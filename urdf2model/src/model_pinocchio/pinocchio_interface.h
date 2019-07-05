
#ifndef PINOCCHIO_INTERFACE_H_INCLUDED
#define PINOCCHIO_INTERFACE_H_INCLUDED

#include <casadi/casadi.hpp>
#include "pinocchio/math/casadi.hpp"

#include "pinocchio/multibody/model.hpp"
#include "pinocchio/parsers/urdf.hpp"
#include "pinocchio/algorithm/frames.hpp"
#include "pinocchio/algorithm/kinematics.hpp"
#include "pinocchio/algorithm/rnea.hpp"
#include "pinocchio/algorithm/aba.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
// #include "pinocchio/algorithm/jacobian.hpp"
// #include "pinocchio/algorithm/crba.hpp"
// #include "pinocchio/algorithm/rnea-derivatives.hpp"
// #include "pinocchio/algorithm/aba-derivatives.hpp"

// Typedef
  typedef double                              Scalar;
  typedef casadi::SX                          CasadiScalar;

  typedef pinocchio::ModelTpl<Scalar>         Model;
  typedef Model::Data                         Data;

  typedef pinocchio::ModelTpl<CasadiScalar>   CasadiModel;
  typedef CasadiModel::Data                   CasadiData;

  typedef Model::ConfigVectorType             ConfigVector;
  typedef Model::TangentVectorType            TangentVector;

  typedef CasadiModel::ConfigVectorType       ConfigVectorCasadi;
  typedef CasadiModel::TangentVectorType      TangentVectorCasadi;


struct Serial_Robot {
   std::string      name;
   int              n_q;
   int              n_joints;
   int              n_dof;
   int              n_bodies;
   int              n_frames;
   std::vector<std::string> joint_names;
   Eigen::VectorXd  gravity;          // Eigen::Vector3d
   Eigen::VectorXd  joint_torque_limit;
   Eigen::VectorXd  joint_pos_ub;
   Eigen::VectorXd  joint_pos_lb;
   Eigen::VectorXd  joint_vel_limit;
   casadi::Function aba;
   casadi::Function rnea;
   casadi::Function fk_pos;
};

Serial_Robot generate_model(std::string filename);

casadi::Function get_forward_dynamics(CasadiModel &cas_model, CasadiData &cas_data);

casadi::Function get_inverse_dynamics(CasadiModel &cas_model, CasadiData &cas_data);

casadi::Function get_forward_kinematics_position(CasadiModel &cas_model, CasadiData &cas_data);

void print_model_data(Serial_Robot robot_info);


#endif // PINOCCHIO_INTERFACE_H_INCLUDED