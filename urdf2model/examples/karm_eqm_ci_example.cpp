#include <casadi/casadi.hpp>
#include "model_interface.hpp"
using namespace std;
int main()
{
    string ws_path = "/home/robot/mpc_ws/urdf2modelcasadi";
  // Example with SFTMP URDF.

  // ---------------------------------------------------------------------
  // Create a model based on a URDF file
  // ---------------------------------------------------------------------
  std::string urdf_filename = ws_path+"/urdf2model/models/HYU/caesar/KARM_EQM_CI.urdf";
  // Instantiate a Serial_Robot object called robot_model
  mecali::Serial_Robot robot_model;
  // Define (optinal) gravity vector to be used
  Eigen::Vector3d gravity_vector(0, 0, -9.81);
  // Eigen::Vector3d gravity_vector(0, 0, 0);
  // Create the model based on a URDF file
  robot_model.import_model(urdf_filename, gravity_vector);
  // robot_model.import_floating_base_model(urdf_filename, gravity_vector, true, true);
  //robot_model.import_planar_base_model(urdf_filename, gravity_vector, true, true);
  // For a floating base robot:
  // q = [global_base_position, global_base_quaternion, joint_positions]
  // v = [local_base_velocity_linear, local_base_velocity_angular, joint_velocities]
  // See: https://github.com/stack-of-tasks/pinocchio/issues/1137

  robot_model.rotorGearRatio << 160, 160, 160, 160, 160, 160, 160;
  robot_model.rotorInertia << 3.371e-4, 3.371e-4, 3.371e-4, 3.371e-4, 3.371e-4, 3.371e-4, 3.371e-4;

  robot_model.set_armature();

  // Print some information related to the imported model (boundaries, frames, DoF, etc)
  robot_model.print_model_data();

  // ---------------------------------------------------------------------
  // Set functions for robot dynamics and kinematics
  // ---------------------------------------------------------------------
  // Set function for forward dynamics
  casadi::Function fd = robot_model.forward_dynamics();
  casadi::Function CoM_x = robot_model.center_of_mass();
  casadi::Function J_com = robot_model.jacobian_center_of_mass();
  // // Set function for inverse dynamics
  casadi::Function id = robot_model.inverse_dynamics();
  casadi::Function M = robot_model.mass_matrix();
  casadi::Function Minv = robot_model.mass_inverse_matrix();
  casadi::Function C = robot_model.coriolis_matrix();
  casadi::Function G = robot_model.generalized_gravity();
  // // Set function for forward kinematics
  std::vector<std::string> required_Frames = {"joint1", "joint2", "joint3", "joint4", "joint5", "joint6", "joint7", "tcp_fixed"};

  std::string end_effector_name = "tcp_fixed";

  casadi::Function fkpos_ee = robot_model.forward_kinematics("position", end_effector_name);
  casadi::Function fkrot_ee = robot_model.forward_kinematics("rotation", end_effector_name);
  casadi::Function fk_ee = robot_model.forward_kinematics("transformation", end_effector_name);
  casadi::Function fk = robot_model.forward_kinematics("transformation",required_Frames);

  casadi::Function J_s = robot_model.kinematic_jacobian("space", end_effector_name);
  casadi::Function J_b = robot_model.kinematic_jacobian("body", end_effector_name);

  casadi::Function dJ_s = robot_model.jacobian_derivative("space", end_effector_name);
  casadi::Function dJ_b = robot_model.jacobian_derivative("body", end_effector_name);


  // ---------------------------------------------------------------------
  // Generate (or save) a function
  // ---------------------------------------------------------------------
  // Code-generate or save a function
  // If you use options, you can set if you want to C-code-generate the function, or just save it as "second_function.casadi" (which can be loaded afterwards using casadi::Function::load("second_function.casadi"))
  mecali::Dictionary codegen_options;
  codegen_options["c"] = true;
  codegen_options["save"] = true;
  mecali::generate_code(fd, "KARM_EQM_CI_fd", codegen_options);
  mecali::generate_code(CoM_x, "KARM_EQM_CI_CoM_x", codegen_options);
  mecali::generate_code(J_com, "KARM_EQM_CI_J_com", codegen_options);
  mecali::generate_code(id, "KARM_EQM_CI_id", codegen_options);
  mecali::generate_code(M, "KARM_EQM_CI_M", codegen_options);
  mecali::generate_code(Minv, "KARM_EQM_CI_Minv", codegen_options);
  mecali::generate_code(C, "KARM_EQM_CI_C", codegen_options);
  mecali::generate_code(G, "KARM_EQM_CI_G", codegen_options);

  mecali::generate_code(fkrot_ee, "KARM_EQM_CI_fkrot_ee", codegen_options);
  mecali::generate_code(fk_ee, "KARM_EQM_CI_fk_ee", codegen_options);
  mecali::generate_code(fk, "KARM_EQM_CI_fk", codegen_options);
  mecali::generate_code(J_s, "KARM_EQM_CI_J_s", codegen_options);
  mecali::generate_code(J_b, "KARM_EQM_CI_J_b", codegen_options);
  mecali::generate_code(dJ_s, "KARM_EQM_CI_dJ_s", codegen_options);
  mecali::generate_code(dJ_b, "KARM_EQM_CI_dJ_b", codegen_options);

  robot_model.generate_json("KARM_EQM_CI.json");

  // std::cout << fd << std::endl;
}
