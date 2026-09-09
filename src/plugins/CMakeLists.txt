# Teach demo trimmed mode:
# only keep teach-related plugins to reduce build size and avoid dragging
# unrelated UI/plugin dependencies.

set(TEACH_DEMO_TRIMMED ON CACHE BOOL "Trimmed teach-demo build mode" FORCE)

# Level 0:
add_subdirectory(coreplugin)

# Level 1: (only depends of Level 0)
add_subdirectory(education/teachcontainer)

# (If present) attach aggregated include paths for trimmed plugins.
if(TARGET TeachDemoPluginCompileIface)
  foreach(_tdp_plugin IN ITEMS Core TeachContainer)
    if(TARGET ${_tdp_plugin})
      get_target_property(_tdp_is_imported ${_tdp_plugin} IMPORTED)
      if(NOT _tdp_is_imported)
        target_link_libraries(${_tdp_plugin} PRIVATE TeachDemoPluginCompileIface)
      endif()
    endif()
  endforeach()
endif()

if(MINGW)
  foreach(_tdp_plugin IN ITEMS Core TeachContainer)
    if(TARGET ${_tdp_plugin})
      get_target_property(_tdp_is_imported ${_tdp_plugin} IMPORTED)
      if(NOT _tdp_is_imported)
        target_compile_options(${_tdp_plugin} PRIVATE -O0 -fno-tree-vectorize)
      endif()
    endif()
  endforeach()
endif()
