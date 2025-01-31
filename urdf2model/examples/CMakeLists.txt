
# link directories (as the -L flag in gcc)
# find_library(CASADI_LIB casadi HINTS ${CASADI_DIR}/lib)

# include directories (as the -I flag in gcc)
include_directories(${PINOCCHIO_INC})
include_directories(${EIGEN_INC})
include_directories(${CASADI_DIR}/install_folder/include)

include_directories(${SRC_DIR})

# Adds an executable target to be built from the source files listed after it
# Basic example
add_executable( basic_example
                basic_example.cpp
              )
target_link_libraries( basic_example

                       ${PROJECT_NAME}
                       ${CASADI_LIB}
                       pinocchio::pinocchio
                     )
# Complete example
add_executable( complete_example
               complete_example.cpp
             )
target_link_libraries( complete_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

# Kinova example
add_executable( kinova_example
                kinova_example.cpp
              )
target_link_libraries( kinova_example

                       ${PROJECT_NAME}
                       ${CASADI_LIB}
                       pinocchio::pinocchio
                     )

add_executable( kinova_2dof_example
               kinova_2dof_example.cpp
             )
target_link_libraries( kinova_2dof_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

## KARM_EM example
add_executable( karm_em_example
              karm_em_example.cpp
              )
target_link_libraries( karm_em_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## KARM_EQM example
add_executable( karm_eqm_example
              karm_eqm_example.cpp
              )
target_link_libraries( karm_eqm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## Caesar example
add_executable( caesar_example
              caesar_example.cpp
              )
target_link_libraries( caesar_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

add_executable( caesar_noload_example
              caesar_noload_example.cpp
              )
target_link_libraries( caesar_noload_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )


# # UR10 example
add_executable( ur10_example
               ur10_example.cpp
             )
target_link_libraries( ur10_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

# # Yumi example
add_executable( yumi_example
               yumi_example.cpp
             )
target_link_libraries( yumi_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )
# # TJ example
add_executable( tj_example
                tj_example.cpp
              )
target_link_libraries( tj_example

                       ${PROJECT_NAME}
                       ${CASADI_LIB}
                       pinocchio::pinocchio
                     )
# # # Gen3 example
add_executable( gen3_example
               gen3_example.cpp
             )
target_link_libraries( gen3_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )
                    
# # # Gen3 lite example
add_executable( gen3_lite_example
               gen3_lite_example.cpp
             )
target_link_libraries( gen3_lite_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

# ## Kinova with gripper example
add_executable( kinova_gripper_example
               kinova_gripper_example.cpp
             )
target_link_libraries( kinova_gripper_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

## iiwa example
add_executable( iiwa_example
               iiwa_example.cpp
             )
target_link_libraries( iiwa_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

## scara example
add_executable( scara_example
               scara_example.cpp
             )
target_link_libraries( scara_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                    )

## KUKA KR250 example
add_executable( kuka_kr250_example
               kuka_kr250_example.cpp
             )
target_link_libraries( kuka_kr250_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )

## KUKA KR120 example
add_executable( kuka_kr120_example
               kuka_kr120_example.cpp
             )
target_link_libraries( kuka_kr120_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )

## KUKA KR60 example
add_executable( kuka_kr60_example
               kuka_kr60_example.cpp
             )
target_link_libraries( kuka_kr60_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )

## KUKA KR5 example
add_executable( kuka_kr5_example
               kuka_kr5_example.cpp
             )
target_link_libraries( kuka_kr5_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )

## Atlas example
add_executable( atlas_example
               atlas_example.cpp
             )
target_link_libraries( atlas_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )


## Rubion example
add_executable( rubion_example
               rubion_example.cpp
             )
target_link_libraries( rubion_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )

## Gen3 float example
add_executable( gen3_float_example
               gen3_float_example.cpp
             )
target_link_libraries( gen3_float_example

                      ${PROJECT_NAME}
                      ${CASADI_LIB}
                      pinocchio::pinocchio
                                        )

## MMO-500 example
add_executable( mmo500_example
              mmo500_example.cpp
              )
target_link_libraries( mmo500_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

add_executable( mmo500_ppr_example
              mmo500_ppr_example.cpp
              )
target_link_libraries( mmo500_ppr_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

add_executable( mmo500_arm_example
              mmo500_arm_example.cpp
              )
target_link_libraries( mmo500_arm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## HYU Mobile Manipulator
add_executable( hyu_mm_example
              hyu_mm_example.cpp
              )
target_link_libraries( hyu_mm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## HYU Mobile
add_executable( hyumob_example
hyumob_example.cpp
)
target_link_libraries( hyumob_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )


## HYU Mobile floating
add_executable( hyumob_floating_example
hyumob_floating_example.cpp
)
target_link_libraries( hyumob_floating_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )

## HYU Mobile offset left
add_executable( hyumob_offset_l_example
hyumob_offset_l_example.cpp
)
target_link_libraries( hyumob_offset_l_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )

## HYU Mobile
add_executable( mobile_example
mobile_example.cpp
)
target_link_libraries( mobile_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )

## HYU Mobile Manipulator
add_executable( hyumm_example
              hyumm_example.cpp
              )
target_link_libraries( hyumm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )


## HYU Mobile Manipulator floating
add_executable( hyumm_floating_example
hyumm_floating_example.cpp
)
target_link_libraries( hyumm_floating_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )

## HYU Mobile Manipulator multi
add_executable( hyumm_multi_example
hyumm_multi_example.cpp
)
target_link_libraries( hyumm_multi_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )

## HYU Mobile Manipulator offset
add_executable( hyumm_offset_l_example
hyumm_offset_l_example.cpp
)
target_link_libraries( hyumm_offset_l_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
           )
add_executable( hyumm_offset_r_example
hyumm_offset_r_example.cpp
)
target_link_libraries( hyumm_offset_r_example

${PROJECT_NAME}
${CASADI_LIB}
pinocchio::pinocchio
          )

## indy7 floating
add_executable( indy7_floating_example
              indy7_floating_example.cpp
              )
target_link_libraries( indy7_floating_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## indy7 dualarm
add_executable( indy7_dualarm_example
              indy7_dualarm_example.cpp
              )
target_link_libraries( indy7_dualarm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## Test ABI: Indy7
add_executable( test_abi_indy7_example
              test_abi_indy7_example.cpp
              )
target_link_libraries( test_abi_indy7_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## Test ABI: Chaser
add_executable( test_abi_chaser_example
              test_abi_chaser_example.cpp
              )
target_link_libraries( test_abi_chaser_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## Soft Morphing
add_executable( sftmp_example
              sftmp_example.cpp
              )
target_link_libraries( sftmp_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## Soft Link
add_executable( sftlink_example
              sftlink_example.cpp
              )
target_link_libraries( sftlink_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## Soft arm
add_executable( softarm_example
              softarm_example.cpp
              )
target_link_libraries( softarm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## Soft arm prismatic
add_executable( softarm_prismatic_example
              softarm_prismatic_example.cpp
              )
target_link_libraries( softarm_prismatic_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )                        

## Soft arm prismatic
add_executable( softarm_prismatic_slack_example
              softarm_prismatic_slack_example.cpp
              )
target_link_libraries( softarm_prismatic_slack_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )   
                                                  
## tetra_mm
add_executable( tetra_mm_example
              tetra_mm_example.cpp
              )
target_link_libraries( tetra_mm_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## mir_m0609
add_executable( mir_m0609_ppr_example
              mir_m0609_ppr_example.cpp
              )
target_link_libraries( mir_m0609_ppr_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## mir250_m0609
add_executable( mir250_m0609_ppr_example
              mir250_m0609_ppr_example.cpp
              )
target_link_libraries( mir250_m0609_ppr_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## mir250
add_executable( mir250_ppr_example
              mir250_ppr_example.cpp
              )
target_link_libraries( mir250_ppr_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## mir_m0609
add_executable( m0609_example
              m0609_example.cpp
              )
target_link_libraries( m0609_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## xArm6
add_executable( xarm6_example
              xarm6_example.cpp
              )
target_link_libraries( xarm6_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## xArm6_ros
add_executable( xarm6_ros_example
              xarm6_ros_example.cpp
              )
target_link_libraries( xarm6_ros_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )
                         
## indy7
add_executable( indy7_example
              indy7_example.cpp
              )
target_link_libraries( indy7_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## indy7_v2
add_executable( indy7_v2_example
              indy7_v2_example.cpp
              )
target_link_libraries( indy7_v2_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

## indyrp2
add_executable( indyrp2_example
              indyrp2_example.cpp
              )
target_link_libraries( indyrp2_example

       ${PROJECT_NAME}
       ${CASADI_LIB}
       pinocchio::pinocchio
                         )

