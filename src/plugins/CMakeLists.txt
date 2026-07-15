# Teach demo trimmed mode:
# only keep teach-related plugins to reduce build size and avoid dragging
# unrelated UI/plugin dependencies.

set(TEACH_DEMO_TRIMMED ON CACHE BOOL "Trimmed teach-demo build mode" FORCE)

# In trimmed demo we prefer importing some large plugins as prebuilt DLLs.
option(TEACH_DEMO_BUILD_SIMULATIONFORM_FROM_SOURCE "Build SimulationForm from source in trimmed demo" OFF)

# Level 0:
add_subdirectory(coreplugin)

# Level 1: (only depends of Level 0)
if(TEACH_DEMO_BUILD_SIMULATIONFORM_FROM_SOURCE)
  add_subdirectory(simulation/simulationform)
else()
  # Import prebuilt SimulationForm plugin (avoid compiling simulation sources).
  set(_td_sim_dll_candidates
    "${PROJECT_SOURCE_DIR}/prebuilt/windows-mingw-x64/bin/libSimulationForm.dll"
  )
  set(_td_sim_implib_candidates
    "${PROJECT_SOURCE_DIR}/prebuilt/windows-mingw-x64/lib/libSimulationForm.dll.a"
  )

  set(_td_sim_dll "")
  foreach(_p IN LISTS _td_sim_dll_candidates)
    if(EXISTS "${_p}")
      set(_td_sim_dll "${_p}")
      break()
    endif()
  endforeach()

  set(_td_sim_implib "")
  foreach(_p IN LISTS _td_sim_implib_candidates)
    if(EXISTS "${_p}")
      set(_td_sim_implib "${_p}")
      break()
    endif()
  endforeach()

  if(NOT _td_sim_dll)
    message(FATAL_ERROR "Teach demo trimmed: prebuilt SimulationForm plugin not found. Searched: ${_td_sim_dll_candidates}")
  endif()

  if(NOT TARGET SimulationForm)
    add_library(SimulationForm SHARED IMPORTED GLOBAL)
    set_target_properties(SimulationForm PROPERTIES IMPORTED_LOCATION "${_td_sim_dll}")
    if(_td_sim_implib)
      set_target_properties(SimulationForm PROPERTIES IMPORTED_IMPLIB "${_td_sim_implib}")
    endif()
    # Provide version metadata for downstream plugins' dependency JSON generation.
    # fun_add_cobot_tp_plugin() reads target property `_arg_VERSION`.
    set_property(TARGET SimulationForm PROPERTY _arg_VERSION "1.0.0")
    set_property(TARGET SimulationForm PROPERTY _arg_COMPAT_VERSION "1.0.0")
  endif()

  # Copy plugin DLL into runtime plugins dir.
  add_custom_target(TeachDemo_CopySimulationForm ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${COBOT_TP_PLUGIN_PATH}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_td_sim_dll}" "${COBOT_TP_PLUGIN_PATH}"
    VERBATIM
  )

  # Copy plugin share data (if present) into teachpendant share dir.
  set(_td_sim_share_candidates
    "${PROJECT_SOURCE_DIR}/share/teachpendant/plugins/SimulationForm"
  )
  foreach(_p IN LISTS _td_sim_share_candidates)
    if(EXISTS "${_p}")
      add_custom_command(TARGET TeachDemo_CopySimulationForm
        COMMAND ${CMAKE_COMMAND} -E make_directory "${COBOT_TP_SHARE_PATH}/plugins/SimulationForm"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${_p}" "${COBOT_TP_SHARE_PATH}/plugins/SimulationForm"
        VERBATIM
      )
      break()
    endif()
  endforeach()
endif()
add_subdirectory(education/teachcontainer)

# (If present) attach aggregated include paths for trimmed plugins.
if(TARGET TeachDemoPluginCompileIface)
  foreach(_tdp_plugin IN ITEMS Core SimulationForm TeachContainer)
    if(TARGET ${_tdp_plugin})
      get_target_property(_tdp_is_imported ${_tdp_plugin} IMPORTED)
      if(NOT _tdp_is_imported)
        target_link_libraries(${_tdp_plugin} PRIVATE TeachDemoPluginCompileIface)
      endif()
    endif()
  endforeach()
endif()

if(MINGW)
  foreach(_tdp_plugin IN ITEMS Core SimulationForm TeachContainer)
    if(TARGET ${_tdp_plugin})
      get_target_property(_tdp_is_imported ${_tdp_plugin} IMPORTED)
      if(NOT _tdp_is_imported)
        target_compile_options(${_tdp_plugin} PRIVATE -O0 -fno-tree-vectorize)
      endif()
    endif()
  endforeach()
endif()
