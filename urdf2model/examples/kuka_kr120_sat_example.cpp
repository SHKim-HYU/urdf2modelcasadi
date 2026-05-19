// =============================================================================
// Robot Model Configuration
// =============================================================================
#define MANUFACTURER    "KUKA"
#define MODEL_NAME      "kuka_kr_120_sat"
#define VERSION         "1.0.0"
// =============================================================================


#include <casadi/casadi.hpp>
#include "model_interface.hpp"
using namespace std;
int main()
{
    string ws_path = "/home/robot/mpc_ws/urdf2modelcasadi";
  // Example with MMO-500 URDF.

  // Create deployer (handles all paths and directories)
    mecali::ModelDeployer deployer(MANUFACTURER, MODEL_NAME);
    deployer.setup_directories();

  // ---------------------------------------------------------------------
  // Create a model based on a URDF file
  // ---------------------------------------------------------------------
  std::string urdf_filename = ws_path+"/urdf2model/models/KUKA/kuka_kr120/kuka_kr_120_sat.urdf";
  // Instantiate a Serial_Robot object called robot_model
  mecali::Serial_Robot robot_model;
  // Define (optinal) gravity vector to be used
  Eigen::Vector3d gravity_vector(0, 0, -9.81);
  robot_model.import_model(urdf_filename, gravity_vector);
  
  robot_model.print_model_data();

  // ---------------------------------------------------------------------
  // Set functions for robot dynamics and kinematics
  // ---------------------------------------------------------------------
  // Set function for forward dynamics
  casadi::Function fd = robot_model.forward_dynamics();
  // // Set function for inverse dynamics
  casadi::Function id = robot_model.inverse_dynamics();
  casadi::Function M = robot_model.mass_matrix();
  casadi::Function Minv = robot_model.mass_inverse_matrix();
  casadi::Function C = robot_model.coriolis_matrix();
  casadi::Function G = robot_model.generalized_gravity();
  
  // // Set function for forward kinematics
  std::vector<std::string> required_Frames = {"r_joint1", "r_joint2", "r_joint3", "r_joint4", "r_joint5", "r_joint6", "tcp_CoM_fixed"};

  std::string ft_frame_name = "r_ft_sensor_joint";
  std::string end_effector_name = "tcp_CoM_fixed";
  

  casadi::Function fkpos_ee = robot_model.forward_kinematics("position", end_effector_name);
  casadi::Function fkrot_ee = robot_model.forward_kinematics("rotation", end_effector_name);
  casadi::Function fk_ft = robot_model.forward_kinematics("transformation", ft_frame_name);
  casadi::Function fk_ee = robot_model.forward_kinematics("transformation", end_effector_name);
  casadi::Function fk = robot_model.forward_kinematics("transformation",required_Frames);

  casadi::Function J_fd = robot_model.forward_dynamics_derivatives("jacobian");
  casadi::Function J_id = robot_model.inverse_dynamics_derivatives("jacobian");

  casadi::Function J_s = robot_model.kinematic_jacobian("space", end_effector_name);
  casadi::Function J_b = robot_model.kinematic_jacobian("body", end_effector_name);

  casadi::Function dJ_s = robot_model.jacobian_derivative("space", end_effector_name);
  casadi::Function dJ_b = robot_model.jacobian_derivative("body", end_effector_name);

  // casadi::Function fk       = robot_model.forward_kinematics("transformation", required_Frames);

  //casadi::Function fk_ee_pos = robot_model.forward_kinematics("position", end_effector_name);

  // ---------------------------------------------------------------------
  // Test the function - Floating base model
  // ---------------------------------------------------------------------
  // std::vector<double> global_base_position = {0.5, 1, 1.5};
  // std::vector<double> global_base_quaternion = {0, 0, 0, 1}; // Identity quaternion
  // std::vector<double> joint_positions = {0.86602540378, 0.5, 0, 1, 0, -0.45, 1, 0, 0};

  // std::vector<double> q_vec;
  // q_vec.insert(q_vec.end(), global_base_position.begin(), global_base_position.end());
  // q_vec.insert(q_vec.end(), global_base_quaternion.begin(), global_base_quaternion.end());
  // q_vec.insert(q_vec.end(), joint_positions.begin(), joint_positions.end());
  // // q = [global_base_position, global_base_quaternion, joint_positions]

  // // Evaluate the function with a casadi::DMVector containing q_vec as input
  // casadi::DM T_res = fk_ee(casadi::DMVector{q_vec})[0];
  // std::cout << "Function result with q_vec input        : " << T_res << std::endl;

  // ---------------------------------------------------------------------
  // Test the function - Planar base model
  // ---------------------------------------------------------------------
  //std::vector<double> global_base_position = {0, 0};
  //std::vector<double> heading_angle_cos_sin = {1, 0};
  //std::vector<double> joint_positions = {0.86602540378, 0.5, 0, 1, 0, -0.45, 1, 0, 0};

  //std::vector<double> q_vec;
  //q_vec.insert(q_vec.end(), global_base_position.begin(), global_base_position.end());
  //q_vec.insert(q_vec.end(), heading_angle_cos_sin.begin(), heading_angle_cos_sin.end());
  //q_vec.insert(q_vec.end(), joint_positions.begin(), joint_positions.end());
  // q = [global_base_position, heading_angle_cos_sin, joint_positions]

  // Evaluate the function with a casadi::DMVector containing q_vec as input
  //casadi::DM T_res = fk_ee(casadi::DMVector{q_vec})[0];
  //std::cout << "Function result with q_vec input        : " << T_res << std::endl;

  // ---------------------------------------------------------------------
  // Generate (or save) a function
  // ---------------------------------------------------------------------
  // Code-generate or save a function
  // If you use options, you can set if you want to C-code-generate the function, or just save it as "second_function.casadi" (which can be loaded afterwards using casadi::Function::load("second_function.casadi"))
  
  mecali::Dictionary codegen_options;
  codegen_options["c"] = true;
  codegen_options["save"] = true;

  std::cout << "\nGenerating CasADi functions..." << std::endl;

  deployer.generate(fd, "fd", codegen_options);
  deployer.generate(id, "id", codegen_options);
  deployer.generate(M, "M", codegen_options);
  deployer.generate(Minv, "Minv", codegen_options);
  deployer.generate(C, "C", codegen_options);
  deployer.generate(G, "G", codegen_options);
  deployer.generate(fk_ft, "fk_ft", codegen_options);
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
  deployer.print_summary();

  // std::cout << fd << std::endl;
}
