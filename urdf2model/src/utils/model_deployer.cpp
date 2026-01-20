#include "model_deployer.hpp"
#include "../model_interface.hpp"
#include <iostream>
#include <boost/version.hpp>

namespace fs = boost::filesystem;

// Boost 1.74+ uses copy_options, older versions use copy_option
#if BOOST_VERSION >= 107400
  #define BOOST_COPY_OVERWRITE fs::copy_options::overwrite_existing
#else
  #define BOOST_COPY_OVERWRITE fs::copy_option::overwrite_if_exists
#endif

namespace mecali
{

ModelDeployer::ModelDeployer(const std::string& manufacturer,
                             const std::string& model_name,
                             const std::string& output_base)
    : manufacturer_(manufacturer),
      model_name_(model_name)
{
    // Build output base path
    output_base_ = output_base + "/" + manufacturer + "/" + model_name;

    // Build all paths
    description_path_ = output_base_ + "/description/";
    meshes_path_ = description_path_ + "meshes/";
    codegen_c_path_ = output_base_ + "/codegen/c/";
    codegen_casadi_path_ = output_base_ + "/codegen/casadi/";
    codegen_lib_path_ = output_base_ + "/codegen/lib/";
    config_path_ = output_base_ + "/config/";
}

void ModelDeployer::setup_directories()
{
    fs::create_directories(description_path_);
    fs::create_directories(meshes_path_);
    fs::create_directories(codegen_c_path_);
    fs::create_directories(codegen_casadi_path_);
    fs::create_directories(codegen_lib_path_);
    fs::create_directories(config_path_);
}

void ModelDeployer::generate(casadi::Function& func, const std::string& name, Dictionary& opts)
{
    std::string full_name = model_name_ + "_" + name;
    generate_code(func,
                  codegen_c_path_ + full_name,
                  codegen_casadi_path_ + full_name,
                  codegen_lib_path_ + full_name,
                  opts);
    // Track generated function
    generated_functions_.insert(name);
}

void ModelDeployer::generate_all(std::vector<std::pair<casadi::Function, std::string>>& functions, Dictionary& opts)
{
    for (auto& pair : functions) {
        generate(pair.first, pair.second, opts);
    }
}

void ModelDeployer::copy_model_files(const std::string& source_model_path)
{
    std::cout << "\nCopying URDF and meshes to description folder..." << std::endl;

    std::string src_urdf = source_model_path + "/" + model_name_ + ".urdf";
    std::string src_meshes = source_model_path + "/meshes/";
    std::string dst_urdf = description_path_ + model_name_ + ".urdf";

    // Copy URDF file
    try {
        if (fs::exists(src_urdf)) {
            fs::copy_file(src_urdf, dst_urdf, BOOST_COPY_OVERWRITE);
            std::cout << "  [URDF]   " << dst_urdf << std::endl;
        } else {
            std::cerr << "  [WARN]   Source URDF not found: " << src_urdf << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "  [WARN]   Failed to copy URDF: " << e.what() << std::endl;
    }

    // Copy meshes directory
    try {
        if (fs::exists(src_meshes) && fs::is_directory(src_meshes)) {
            for (fs::directory_iterator it(src_meshes); it != fs::directory_iterator(); ++it) {
                std::string dst_mesh = meshes_path_ + it->path().filename().string();
                fs::copy_file(it->path(), dst_mesh, BOOST_COPY_OVERWRITE);
                std::cout << "  [MESH]   " << dst_mesh << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "  [WARN]   Failed to copy meshes: " << e.what() << std::endl;
    }
}

void ModelDeployer::generate_config(Serial_Robot& robot)
{
    std::string config_file = config_path_ + model_name_ + ".json";
    robot.generate_json(config_file, output_base_, codegen_lib_path_, get_urdf_path(), model_name_, generated_functions_);
}

void ModelDeployer::print_summary() const
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "Code generation completed!" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Output structure:" << std::endl;
    std::cout << "  " << output_base_ << "/" << std::endl;
    std::cout << "    ├── description/" << std::endl;
    std::cout << "    │   ├── " << model_name_ << ".urdf" << std::endl;
    std::cout << "    │   └── meshes/*.stl" << std::endl;
    std::cout << "    ├── codegen/" << std::endl;
    std::cout << "    │   ├── c/*.c" << std::endl;
    std::cout << "    │   ├── casadi/*.casadi" << std::endl;
    std::cout << "    │   └── lib/*.so" << std::endl;
    std::cout << "    └── config/" << std::endl;
    std::cout << "        └── " << model_name_ << ".json" << std::endl;
    std::cout << "========================================" << std::endl;
}

} // namespace mecali
