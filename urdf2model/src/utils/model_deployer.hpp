#ifndef UTILS_MODEL_DEPLOYER_H_INCLUDED
#define UTILS_MODEL_DEPLOYER_H_INCLUDED

#include "../functions/common.hpp"
#include "code_generation.hpp"
#include <boost/filesystem.hpp>
#include <vector>
#include <set>
#include <functional>

namespace mecali
{
  // Forward declaration
  class Serial_Robot;

  /**
   * @brief Handles robot model deployment: directory setup, code generation, and file copying
   */
  class ModelDeployer
  {
  public:
    /**
     * @brief Construct a ModelDeployer
     * @param manufacturer Manufacturer name (e.g., "HDRobotics")
     * @param model_name Model name (e.g., "yl012")
     * @param output_base Base output path (default: "/opt/robot_foundation/models/robots")
     */
    ModelDeployer(const std::string& manufacturer,
                  const std::string& model_name,
                  const std::string& output_base = "/opt/robot_foundation/models/robots");

    /**
     * @brief Create all necessary output directories
     */
    void setup_directories();

    /**
     * @brief Generate code for a single CasADi function
     * @param func CasADi function to generate
     * @param name Function name suffix (e.g., "fd", "id", "M")
     * @param opts Code generation options
     */
    void generate(casadi::Function& func, const std::string& name, Dictionary& opts);

    /**
     * @brief Generate code for multiple CasADi functions
     * @param functions Vector of pairs (function, name)
     * @param opts Code generation options
     */
    void generate_all(std::vector<std::pair<casadi::Function, std::string>>& functions, Dictionary& opts);

    /**
     * @brief Copy URDF and mesh files from source to output description folder
     * @param source_model_path Path to source model directory containing URDF and meshes/
     */
    void copy_model_files(const std::string& source_model_path);

    /**
     * @brief Generate JSON config file
     * @param robot The robot model to generate config for
     */
    void generate_config(Serial_Robot& robot);

    /**
     * @brief Print deployment summary
     */
    void print_summary() const;

    // Path getters
    std::string get_output_base() const { return output_base_; }
    std::string get_description_path() const { return description_path_; }
    std::string get_meshes_path() const { return meshes_path_; }
    std::string get_codegen_c_path() const { return codegen_c_path_; }
    std::string get_codegen_casadi_path() const { return codegen_casadi_path_; }
    std::string get_codegen_lib_path() const { return codegen_lib_path_; }
    std::string get_config_path() const { return config_path_; }
    std::string get_model_prefix() const { return model_name_; }
    std::string get_urdf_path() const { return description_path_ + model_name_ + ".urdf"; }

  private:
    std::string manufacturer_;
    std::string model_name_;
    std::string output_base_;
    std::string description_path_;
    std::string meshes_path_;
    std::string codegen_c_path_;
    std::string codegen_casadi_path_;
    std::string codegen_lib_path_;
    std::string config_path_;
    std::set<std::string> generated_functions_;  // Track which functions were generated
  };

} // namespace mecali

#endif // UTILS_MODEL_DEPLOYER_H_INCLUDED
