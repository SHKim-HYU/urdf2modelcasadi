#include "code_generation.hpp"
#include <cstdlib>
#include <cstdio>

namespace mecali
{
  void generate_code(casadi::Function& func, std::string name)
  {
    func.generate(name+".c");
  }

  void generate_code(casadi::Function& func, std::string name, Dictionary& opts)
  {
    #ifdef DEBUG
      if (opts.find("c") != opts.end() || opts.find("save") != opts.end())
      {
        std::cout << "** Code generating function \"" << func.name() << "\" in: " << std::endl;
      }
    #endif

    if (opts.find("c") != opts.end())  // If there exists a key "c" inside opts
    {
      if (opts["c"])      // If key "c" was set to true
      {
          #ifdef DEBUG
            std::cout << "\t C ... \t\t" << name << ".c" << std::endl;
          #endif
          func.generate(name+".c");
      }
    }
    if (opts.find("save") != opts.end())  // If there exists a key "save" inside opts
    {
      if (opts["save"])
      {
          #ifdef DEBUG
            std::cout << "\t CasADi save ... \t" << name << ".m" << std::endl;
          #endif
          func.save(name+".casadi");
      }
    }
  }

  void generate_code(casadi::Function& func,
                     const std::string& c_path,
                     const std::string& casadi_path,
                     const std::string& lib_path,
                     Dictionary& opts)
  {
    std::string func_name = func.name();

    // Extract just the filename from the path
    size_t last_slash = c_path.find_last_of('/');
    std::string base_name = (last_slash != std::string::npos) ? c_path.substr(last_slash + 1) : c_path;

    // Generate .c file (CasADi generates in current dir with just filename)
    if (opts.find("c") != opts.end() && opts["c"])
    {
      std::string c_file = c_path + ".c";
      std::string temp_c = base_name + ".c";

      // Generate to current directory
      func.generate(temp_c);

      // Move to target directory
      std::string mv_cmd = "mv " + temp_c + " " + c_file;
      int ret = system(mv_cmd.c_str());
      if (ret == 0) {
        std::cout << "  [C]      " << c_file << std::endl;
      } else {
        std::cerr << "  [WARN]   Failed to move " << temp_c << " to " << c_file << std::endl;
      }

      // Compile to .so if requested
      if (opts.find("compile") != opts.end() && opts["compile"])
      {
        std::string so_file = lib_path + ".so";
        std::string cmd = "gcc -shared -fPIC -O3 " + c_file + " -o " + so_file + " 2>/dev/null";
        ret = system(cmd.c_str());
        if (ret == 0) {
          std::cout << "  [SO]     " << so_file << std::endl;
        } else {
          std::cerr << "  [WARN]   Failed to compile " << so_file << std::endl;
        }
      }
    }

    // Save .casadi file
    if (opts.find("save") != opts.end() && opts["save"])
    {
      std::string casadi_file = casadi_path + ".casadi";
      std::string temp_casadi = base_name + ".casadi";

      // Save to current directory
      func.save(temp_casadi);

      // Move to target directory
      std::string mv_cmd = "mv " + temp_casadi + " " + casadi_file;
      int ret = system(mv_cmd.c_str());
      if (ret == 0) {
        std::cout << "  [CASADI] " << casadi_file << std::endl;
      } else {
        std::cerr << "  [WARN]   Failed to move " << temp_casadi << " to " << casadi_file << std::endl;
      }
    }
  }
}
