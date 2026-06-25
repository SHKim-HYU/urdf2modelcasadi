// =============================================================================
// Robot Model Configuration
// =============================================================================
#define MANUFACTURER    "HDRobotics"
#define MODEL_NAME      "yl012"
#define VERSION         "1.0.0"
// =============================================================================

#include <casadi/casadi.hpp>
#include "model_interface.hpp"

using namespace std;

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "Robot Model Code Generator" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Manufacturer: " << MANUFACTURER << std::endl;
    std::cout << "Model Name:   " << MODEL_NAME << std::endl;
    std::cout << "Version:      " << VERSION << std::endl;
    std::cout << "========================================" << std::endl;

    // Create deployer (handles all paths and directories)
    mecali::ModelDeployer deployer(MANUFACTURER, MODEL_NAME);
    deployer.setup_directories();

    std::cout << "Output:       " << deployer.get_output_base() << std::endl;

    // Get URDF path from environment or default
    std::string ws_path = std::string(getenv("URDF2MODELCASADI_PATH") ? getenv("URDF2MODELCASADI_PATH") : ".");
    std::string source_model = ws_path + "/urdf2model/models/" + MANUFACTURER + "/" + MODEL_NAME;
    std::string urdf_filename = source_model + "/" + MODEL_NAME + ".urdf";

    // ---------------------------------------------------------------------
    // Create a model based on a URDF file
    // ---------------------------------------------------------------------
    mecali::Serial_Robot robot_model;
    Eigen::Vector3d gravity_vector(0, 0, -9.81);
    robot_model.import_model(urdf_filename, gravity_vector);

    robot_model.rotorGearRatio << 100, 120, 100, 100, 100, 100;
    robot_model.rotorInertia << 6.6e-5, 1.39e-4, 6.6e-5, 2.0e-5, 2.0e-5, 1.3e-5;

    robot_model.print_model_data();

    // ---------------------------------------------------------------------
    // Set functions for robot dynamics and kinematics
    // ---------------------------------------------------------------------
    casadi::Function fd = robot_model.forward_dynamics();
    casadi::Function CoM_x = robot_model.center_of_mass();
    casadi::Function id = robot_model.inverse_dynamics();
    casadi::Function M = robot_model.mass_matrix();
    casadi::Function Minv = robot_model.mass_inverse_matrix();
    casadi::Function C = robot_model.coriolis_matrix();
    casadi::Function G = robot_model.generalized_gravity();

    std::string end_effector_name = "tcp_fixed";
    std::vector<std::string> required_Frames = {"joint0", "joint1", "joint2", "joint3", "joint4", "joint5", "tcp_fixed"};

    casadi::Function fkrot_ee = robot_model.forward_kinematics("rotation", end_effector_name);
    casadi::Function fk_ee = robot_model.forward_kinematics("transformation", end_effector_name);
    casadi::Function fk = robot_model.forward_kinematics("transformation", required_Frames);

    casadi::Function J_fd = robot_model.forward_dynamics_derivatives("jacobian");
    casadi::Function J_id = robot_model.inverse_dynamics_derivatives("jacobian");

    casadi::Function J_s = robot_model.kinematic_jacobian("space", end_effector_name);
    casadi::Function J_b = robot_model.kinematic_jacobian("body", end_effector_name);

    casadi::Function dJ_s = robot_model.jacobian_derivative("space", end_effector_name);
    casadi::Function dJ_b = robot_model.jacobian_derivative("body", end_effector_name);

    // ---------------------------------------------------------------------
    // Generate code using ModelDeployer
    // ---------------------------------------------------------------------
    mecali::Dictionary codegen_options;
    codegen_options["c"] = true;
    codegen_options["save"] = true;
    codegen_options["compile"] = true;

    std::cout << "\nGenerating CasADi functions..." << std::endl;

    deployer.generate(fd, "fd", codegen_options);
    deployer.generate(CoM_x, "CoM_x", codegen_options);
    deployer.generate(id, "id", codegen_options);
    deployer.generate(M, "M", codegen_options);
    deployer.generate(Minv, "Minv", codegen_options);
    deployer.generate(C, "C", codegen_options);
    deployer.generate(G, "G", codegen_options);
    deployer.generate(fkrot_ee, "fkrot_ee", codegen_options);
    deployer.generate(fk_ee, "fk_ee", codegen_options);
    deployer.generate(fk, "fk", codegen_options);
    deployer.generate(J_fd, "J_fd", codegen_options);
    deployer.generate(J_id, "J_id", codegen_options);
    deployer.generate(J_s, "J_s", codegen_options);
    deployer.generate(J_b, "J_b", codegen_options);
    deployer.generate(dJ_s, "dJ_s", codegen_options);
    deployer.generate(dJ_b, "dJ_b", codegen_options);

    // Generate JSON config and copy model files
    deployer.generate_config(robot_model);
    deployer.copy_model_files(source_model);
    deployer.print_summary();

    return 0;
}
