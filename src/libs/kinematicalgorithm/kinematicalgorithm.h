#pragma once
#include "kinematicalgorithm_global.h"
#include "kinematicalgorithmtype.h"

KINEMATICALGORITHM_EXPORT int Ino_Kine_WobjPosToJoint(KinematicAlgorithmSpace::RobPos wobjPos,
                                                      KinematicAlgorithmSpace::ToolData tool,
                                                      KinematicAlgorithmSpace::WobjData wobj,
                                                      KinematicAlgorithmSpace::LoadData payload,
                                                      KinematicAlgorithmSpace::JPos *pJointPos);

KINEMATICALGORITHM_EXPORT int Ino_Kine_WobjPosToJoint_Ptr(KinematicAlgorithmSpace::RobPos *pWobjPos,
                                                          KinematicAlgorithmSpace::ToolData *pTool,
                                                          KinematicAlgorithmSpace::WobjData *pWobj,
                                                          KinematicAlgorithmSpace::LoadData *pPayload,
                                                          KinematicAlgorithmSpace::JPos *pJointPos);
