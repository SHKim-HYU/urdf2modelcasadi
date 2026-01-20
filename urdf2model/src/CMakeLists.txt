

SET(${PROJECT_NAME}_SOURCES)
LIST(APPEND ${PROJECT_NAME}_SOURCES

    ${SRC_DIR}/model_interface.cpp
    ${SRC_DIR}/functions/forward_dynamics.cpp
    ${SRC_DIR}/functions/inverse_dynamics.cpp
    ${SRC_DIR}/functions/forward_kinematics.cpp
    ${SRC_DIR}/functions/robot_expressions.cpp
    ${SRC_DIR}/utils/code_generation.cpp
    ${SRC_DIR}/utils/model_deployer.cpp
    )

# include directories (as the -I flag in gcc)
include_directories(${PINOCCHIO_INC})
include_directories(/usr/include/eigen3)

# link external libraries (as the -l flag in gcc)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${HEADERS} ${${PROJECT_NAME}_SOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# target link libraries
target_link_libraries(${PROJECT_NAME}

                      stdc++
                      boost_system
                      boost_filesystem
                      urdfdom_model
                      ${CASADI_LIB}
                    )

# Install
# ADD_HEADER_GROUP(HEADERS)
# ADD_SOURCE_GROUP(${PROJECT_NAME}_SOURCES)
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION lib)

# MESSAGE( STATUS "HEADERS is: " ${HEADERS} )
# MESSAGE( STATUS "{{PROJECT_NAME}_SOURCES} is: " ${${PROJECT_NAME}_SOURCES} )
