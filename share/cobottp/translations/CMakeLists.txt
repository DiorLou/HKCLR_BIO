set(_td_qm_dir "${ProjectPath}/rc/share/teachpendant/translations")
set(_td_qm_files
  "${_td_qm_dir}/cobottp_en.qm"
  "${_td_qm_dir}/cobottp_zh_CN.qm"
)

foreach(_f IN LISTS _td_qm_files)
  if(NOT EXISTS "${_f}")
    message(FATAL_ERROR "Missing required translation file: ${_f}")
  endif()
endforeach()

install(FILES ${_td_qm_files} DESTINATION "${APP_DATA_PATH}/translations")
