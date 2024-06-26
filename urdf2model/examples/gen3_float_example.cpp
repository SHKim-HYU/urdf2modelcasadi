#include <casadi/casadi.hpp>
#include "model_interface.hpp"
using namespace std;
int main()
{
  // Example with UR10 URDF.

  // ---------------------------------------------------------------------
  // Create a model based on a URDF file
  // ---------------------------------------------------------------------
  std::string urdf_filename = "../urdf2model/models/kortex_description/urdf/JACO3_URDF_V11lim.urdf";
  // Instantiate a Serial_Robot object called robot_model
  mecali::Serial_Robot robot_model;
  // Define (optinal) gravity vector to be used
  // Eigen::Vector3d gravity_vector(0, 0, -9.81);
  Eigen::Vector3d gravity_vector(0, 0, 0);
  // Create the model based on a URDF file
  // robot_model.import_model(urdf_filename, gravity_vector);
  robot_model.import_floating_base_model(urdf_filename, gravity_vector, true, true);

  // Print some information related to the imported model (boundaries, frames, DoF, etc)
  robot_model.print_model_data();

  // ---------------------------------------------------------------------
  // Set functions for robot dynamics and kinematics
  // ---------------------------------------------------------------------
  // Set function for forward dynamics
  casadi::Function fwd_dynamics = robot_model.forward_dynamics();
  // // Set function for inverse dynamics
  //   casadi::Function inv_dynamics = robot_model.inverse_dynamics();
  // // Set function for forward kinematics
  // std::vector<std::string> required_Frames = {"Actuator1", "Actuator2", "Actuator3", "Actuator4", "Actuator5", "Actuator6", "Actuator7", "EndEffector" };

  casadi::Function fkpos_ee = robot_model.forward_kinematics("position", "EndEffector");
  // casadi::Function fkrot_ee = robot_model.forward_kinematics("rotation", "EndEffector");
  // casadi::Function fk_ee    = robot_model.forward_kinematics("transformation", "EndEffector");
  // casadi::Function fk       = robot_model.forward_kinematics("transformation", required_Frames);
  // casadi::Function fd       = robot_model.forward_dynamics();
  // casadi::Function id       = robot_model.inverse_dynamics();

  // robot_model.generate_json("kinova.json");

  std::cout << "FLOPS FD: " << fwd_dynamics.n_instructions() << " ----> " << fwd_dynamics << std::endl;
  std::cout << "FLOPS FK: " << fkpos_ee.n_instructions() << " ----> " << fkpos_ee << std::endl;

  // FLOPS FD: 3633 ----> aba:(q[7],dq[7],tau[7])->(ddq[7]) SXFunction
  // FLOPS FK: 476 ----> fk_pos:(q[7])->(Pos_EndEffector[3]) SXFunction

  // FLOPS FD: 5466 ----> aba:(q[14],dq[13],tau[13])->(ddq[13]) SXFunction
  // FLOPS FK: 568 ----> fk_pos:(q[14])->(Pos_EndEffector[3]) SXFunction

  // ---------------------------------------------------------------------
  // Generate (or save) a function
  // ---------------------------------------------------------------------
  // Code-generate or save a function
  // If you use options, you can set if you want to C-code-generate the function, or just save it as "second_function.casadi" (which can be loaded afterwards using casadi::Function::load("second_function.casadi"))
  // mecali::Dictionary codegen_options;
  // codegen_options["c"]=false;
  // codegen_options["save"]=true;
  // mecali::generate_code(fkpos_ee, "kinova_fkpos_ee", codegen_options);
  // mecali::generate_code(fkrot_ee, "kinova_fkrot_ee", codegen_options);
  // mecali::generate_code(fk_ee, "kinova_fk_ee", codegen_options);
  // mecali::generate_code(fk, "kinova_fk", codegen_options);
  // mecali::generate_code(fd, "kinova_fd", codegen_options);
  // mecali::generate_code(id, "kinova_id", codegen_options);
}
