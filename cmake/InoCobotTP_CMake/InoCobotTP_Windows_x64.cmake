set(COBOT_TP_APP_TARGET "InoCobotTP")
set(SOURCE_FILE_BIN ${CMAKE_BINARY_DIR}/bin)
set(DESTINATION_FILE_BIN ${CMAKE_BINARY_DIR}/${COBOT_TP_APP_TARGET}/bin)
set(SOURCE_FILE_SHARE ${CMAKE_BINARY_DIR}/share)
set(DESTINATION_FILE_SHARE ${CMAKE_BINARY_DIR}/${COBOT_TP_APP_TARGET}/share)

#Delete other .exe
file(GLOB ALL_EXE_FILES "${SOURCE_FILE_BIN}/*.exe")
foreach(EXE ${ALL_EXE_FILES})
   get_filename_component(EXE_FILE_NAME ${EXE} NAME_WE)
   if(NOT EXE_FILE_NAME STREQUAL COBOT_TP_APP_TARGET)
       file(REMOVE ${EXE})
   endif()
endforeach()

set(PluginLib_UserManualForm_Enabled ON)

