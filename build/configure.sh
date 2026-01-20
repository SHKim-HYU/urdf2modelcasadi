#!/bin/bash
# =============================================================================
# urdf2modelcasadi Build & Deploy Script
# =============================================================================

# Declare TPUT dictionary for readability
  declare -A TPUT=( ["CYAN"]=$(tput setaf 6) ["GREEN"]=$(tput setaf 2) ["YELLOW"]=$(tput setaf 3) ["RED"]=$(tput setaf 1) ["NORMAL"]=$(tput sgr0) ["BOLD"]=$(tput bold))
  print_title () {
      printf "\n%40s\n" "${TPUT[CYAN]}${TPUT[BOLD]} $1 ${TPUT[NORMAL]}"
  }
  print_success () {
      printf "${TPUT[GREEN]}${TPUT[BOLD]}[OK]${TPUT[NORMAL]} %s\n" "$1"
  }
  print_warn () {
      printf "${TPUT[YELLOW]}${TPUT[BOLD]}[WARN]${TPUT[NORMAL]} %s\n" "$1"
  }

# =============================================================================
# Configuration
# =============================================================================
  export PINOCCHIO_INCLUDE="/opt/openrobots/include/"
  export EIGEN_INCLUDE="/usr/include/eigen3"
  export INSTALL_FOLDER="/opt/urdf2modelcasadi"

  # Get script directory and project root
  SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

  # Set URDF2MODELCASADI_PATH for example programs
  export URDF2MODELCASADI_PATH="$PROJECT_ROOT"

  # Robot Foundation path
  ROBOT_FOUNDATION_PATH="/opt/Robot_Foundation/models/robot"

# If the CMakeCache.txt file exists, delete it.
  if test -f "CMakeCache.txt"; then
      print_title "########## Removing CMakeCache.txt ##########"
      rm CMakeCache.txt
      # ls | grep -v configure.sh | xargs rm -r # deletes everything, except configure.sh
      #rm -rf CMakeFiles
      #rm *.so Makefile urdf2model_casadi *.cmake
      printf "   CMakeCache.txt removed\n"
  fi

# Execute the cmake command, assigning the variable reference values (CASADI_DIR, PINOCCHIO_INC, EIGEN_INC).
  print_title "########## Executing CMake ##########"
  # cmake ../urdf2model -DCASADI_DIR=$CASADI_DIRECTORY -DPINOCCHIO_INC=$PINOCCHIO_INCLUDE -DEIGEN_INC=$EIGEN_INCLUDE
  # cmake ../urdf2model -DCASADI_DIR=$CASADI_DIRECTORY -DPINOCCHIO_INC=$PINOCCHIO_INCLUDE -DEIGEN_INC=$EIGEN_INCLUDE -DBUILD_UNIT_TESTS=ON -DDEBUG_MODE=ON
  cmake ../urdf2model -DCASADI_DIR=$ENV{CASADI_DIRECTORY} -DPINOCCHIO_INC=$PINOCCHIO_INCLUDE -DEIGEN_INC=$EIGEN_INCLUDE -DCMAKE_INSTALL_PREFIX=$INSTALL_FOLDER -DCMAKE_BUILD_TYPE=Release
  # cmake ../urdf2model -DCASADI_DIR=$CASADI_DIRECTORY -DPINOCCHIO_INC=$PINOCCHIO_INCLUDE -DEIGEN_INC=$EIGEN_INCLUDE -DCMAKE_INSTALL_PREFIX=$INSTALL_FOLDER
# Execute the make command
  print_title "########## Executing make ##########"
  make -j$(nproc)
  # make

# Execute unit tests
  print_title "########## Executing unit tests ##########"
  export BOOST_TEST_LOG_LEVEL="message"
  # # ctest -V
  make test ARGS="-j3 -V" # -V

# Execute the make install command
  print_title "########## Installing the library ##########"
  # make install

# =============================================================================
# Deploy Robot Models
# =============================================================================
deploy_model() {
    local example_name=$1
    print_title "########## Deploying $example_name ##########"

    # Create Robot Foundation directory if it doesn't exist
    if [ ! -d "$ROBOT_FOUNDATION_PATH" ]; then
        print_warn "Creating Robot Foundation directory: $ROBOT_FOUNDATION_PATH"
        sudo mkdir -p "$ROBOT_FOUNDATION_PATH"
        sudo chown -R $(whoami):$(whoami) "$ROBOT_FOUNDATION_PATH"
    fi

    # Run the example to generate and deploy files
    if [ -f "./examples/${example_name}_example" ]; then
        echo "Running ${example_name}_example..."
        ./examples/${example_name}_example
        print_success "Deployed $example_name to $ROBOT_FOUNDATION_PATH"
    else
        print_warn "Example not found: ./examples/${example_name}_example"
    fi
}

# Check for deploy argument
if [ "$1" == "--deploy" ]; then
    shift
    if [ -z "$1" ]; then
        print_warn "Usage: ./configure.sh --deploy <model_name>"
        print_warn "Example: ./configure.sh --deploy yl012"
        exit 1
    fi
    deploy_model "$1"
elif [ "$1" == "--deploy-all" ]; then
    print_title "########## Deploying All Models ##########"
    # List of models to deploy (add more as needed)
    MODELS=("yl012" "indy7" "karm_em")
    for model in "${MODELS[@]}"; do
        deploy_model "$model"
    done
fi

# =============================================================================
# Summary
# =============================================================================
print_title "########## Build Complete ##########"
echo ""
echo "To deploy a specific robot model:"
echo "  ./configure.sh --deploy <model_name>"
echo ""
echo "Example:"
echo "  ./configure.sh --deploy yl012"
echo ""
echo "Output will be generated at:"
echo "  $ROBOT_FOUNDATION_PATH/<manufacturer>/<model>/"
echo "    ├── description/"
echo "    │   ├── <model>.urdf"
echo "    │   └── meshes/"
echo "    ├── codegen/"
echo "    │   ├── c/*.c"
echo "    │   ├── casadi/*.casadi"
echo "    │   └── lib/*.so"
echo "    └── config/"
echo "        └── <model>.json"
echo ""
