#ifndef UTILS_CODE_GENERATION_H_INCLUDED
#define UTILS_CODE_GENERATION_H_INCLUDED

#include "../functions/common.hpp"

namespace mecali
{
  void generate_code(casadi::Function& func, std::string name);
  void generate_code(casadi::Function& func, std::string name, Dictionary& opts);
  // New overload with separate paths for .c, .casadi, and .so files
  void generate_code(casadi::Function& func,
                     const std::string& c_path,
                     const std::string& casadi_path,
                     const std::string& lib_path,
                     Dictionary& opts);
}

#endif // UTILS_CODE_GENERATION_H_INCLUDED
