include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FunPrivate.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/DebugMessage.cmake)

set(COBOT_TP_VERSION 1.0.0)
set(COBOT_TP_APP_TARGET             "InoCobotTP")
set(COBOT_TP_BIN_PATH               ${CMAKE_BINARY_DIR}/bin)
set(COBOT_TP_APP_PATH               ${COBOT_TP_BIN_PATH})
set(COBOT_TP_LIBRARY_BASE_PATH      ${COBOT_TP_BIN_PATH})
set(COBOT_TP_LIBRARY_PATH           ${COBOT_TP_BIN_PATH})
set(COBOT_TP_LIBEXEC_PATH           ${COBOT_TP_BIN_PATH})
set(COBOT_TP_PLUGIN_PATH            ${COBOT_TP_BIN_PATH}/plugins)
set(COBOT_TP_LIBRARY_ARCHIVE_PATH   ${COBOT_TP_BIN_PATH}/libs)
set(COBOT_TP_DEP_LIB_PATH           ${CMAKE_BINARY_DIR}/lib)

set(COBOT_TP_DATA_PATH              ${CMAKE_BINARY_DIR}/share)
set(COBOT_TP_DOC_PATH               ${CMAKE_BINARY_DIR}/share/doc)
set(COBOT_TP_SHARE_PATH             ${CMAKE_BINARY_DIR}/share/teachpendant)
set(COBOT_TP_SDK_SHARE_PATH         ${CMAKE_BINARY_DIR}/share/sdk)
set(COBOT_TP_HEADER_INSTALL_PATH    "")
set(COBOT_TP_CMAKE_INSTALL_PATH     ${CMAKE_BINARY_DIR}/cmake)
set(APP_DATA_PATH "${_APP_DATA_PATH}")     # The APP data path (relative to CMAKE_INSTALL_PREFIX).

set(COBOT_TP_HEADER_INSTALL_PATH    "${COBOT_TP_HEADER_INSTALL_PATH}")
set(COBOT_TP_CMAKE_INSTALL_PATH     "${COBOT_TP_CMAKE_INSTALL_PATH}")

file(RELATIVE_PATH RELATIVE_PLUGIN_PATH ${COBOT_TP_APP_PATH} ${COBOT_TP_PLUGIN_PATH})
file(RELATIVE_PATH RELATIVE_SHARE_PATH  ${COBOT_TP_APP_PATH} ${COBOT_TP_SHARE_PATH})
file(RELATIVE_PATH RELATIVE_SDK_SHARE_PATH ${COBOT_TP_APP_PATH}  ${COBOT_TP_SDK_SHARE_PATH})
file(RELATIVE_PATH RELATIVE_DEP_LIB_PATH   ${COBOT_TP_APP_PATH} ${COBOT_TP_DEP_LIB_PATH})
file(RELATIVE_PATH FROM_PLUGIN_TO_LIB ${COBOT_TP_PLUGIN_PATH} ${COBOT_TP_LIBRARY_PATH})

if(COBOT_ANDROID)
    set(COBOT_TP_BIN_PATH               ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_APP_PATH               ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_LIBRARY_BASE_PATH      ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_LIBRARY_PATH           ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_LIBEXEC_PATH           ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_PLUGIN_PATH            ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_LIBRARY_ARCHIVE_PATH   ${CMAKE_BINARY_DIR}/src/app)
    set(COBOT_TP_DEP_LIB_PATH           ${CMAKE_BINARY_DIR}/src/app)
    if(CUSTOM_DEPLOY_ANDROID)
        set(SO_OUTPUT_PATH ${CMAKE_BINARY_DIR}/src/app/android-build/libs/${COBOT_TP_ANDROID_ABI})
    endif()
endif()

# CMake>3.17 以上可以使用CMAKE_CURRENT_FUNCTION_LIST_DIR
set(_THIS_MODULE_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")

option(BUILD_PLUGINS_BY_DEFAULT "Build as plugins by default." ON)
option(BUILD_EXECUTABLES_BY_DEFAULT "Build executables by default." ON)
option(BUILD_LIBRARIES_BY_DEFAULT "Build libraries by default. " ON)
option(BUILD_TESTS_BY_DEFAULT "Build tests by default. " ON)
option(Separate_Debug_Message "Extract debug information from binary files." OFF)


function(process_list_default_value list_type)
  set(PLUGINS_single plugin)
  set(EXECUTABLES_single executable)
  set(LIBRARIES_single library)
  set(TESTS_single test)

  if (NOT DEFINED BUILD_${list_type})
      return()
  endif()

  set(BUILD_${list_type}_BY_DEFAULT OFF CACHE BOOL "" FORCE)

  foreach(element ${BUILD_${list_type}})
    string(TOUPPER "${${list_type}_single}_${element}" upper_element)
    set(BUILD_${upper_element} ON CACHE BOOL "Build ${${list_type}_single} ${element}.")
  endforeach()
endfunction()

process_list_default_value(PLUGINS)
process_list_default_value(EXECUTABLES)
process_list_default_value(LIBRARIES)
process_list_default_value(TESTS)

function(cobot_tp_plugin_enabled varName name)
  if (NOT (name IN_LIST __COBOT_PLUGINS))
    message(FATAL_ERROR "cobot_tp_plugin_enabled: Unknown plugin target \"${name}\"")
  endif()
  if (TARGET ${name})
    set(${varName} ON PARENT_SCOPE)
  else()
    set(${varName} OFF PARENT_SCOPE)
  endif()
endfunction()

function(cobot_tp_library_enabled varName name)
  if (NOT (name IN_LIST __COBOT_LIBRARIES))
    message(FATAL_ERROR "cobot_tp_library_enabled: Unknown library target \"${name}\"")
  endif()
  if (TARGET ${name})
    set(${varName} ON PARENT_SCOPE)
  else()
    set(${varName} OFF PARENT_SCOPE)
  endif()
endfunction()

function(fun_add_cobot_tp_library name)
  cmake_parse_arguments(_arg "STATIC;OBJECT;SKIP_TRANSLATION;FEATURE_INFO"
      "DESTINATION;COMPONENT;SOURCES_PREFIX;BUILD_DEFAULT"
      "CONDITION;DEPENDS;PUBLIC_DEPENDS;DEFINES;PUBLIC_DEFINES;INCLUDES;PUBLIC_INCLUDES;SOURCES;EXPLICIT_MOC;SKIP_AUTOMOC;EXTRA_TRANSLATIONS;PROPERTIES" ${ARGN}
    )

  set(global_defines_copy ${GLOBAL_DEFINES})

  if (${_arg_UNPARSED_ARGUMENTS})
    message(FATAL_ERROR "Error! Unparsed arguments in function <fun_add_cobot_tp_library>!")
  endif()

  refresh_global_cache(__COBOT_LIBRARIES "${name}")

  condition_info(_extra_text _arg_CONDITION)
  if (NOT _arg_CONDITION)
    set(_arg_CONDITION ON)
  endif()

  string(TOUPPER "BUILD_LIBRARY_${name}" _build_library_var)

  if (DEFINED _arg_BUILD_DEFAULT)
    set(_build_library_default ${_arg_BUILD_DEFAULT})
  else()
    set(_build_library_default ${BUILD_LIBRARIES_BY_DEFAULT})
  endif()

  set(${_build_library_var} "${_build_library_default}" CACHE BOOL "Build library ${name}.")
  if ((${_arg_CONDITION}) AND ${_build_library_var})
    set(_library_enabled ON)
  else()
    set(_library_enabled OFF)
  endif()

  if(DEFINED _arg_FEATURE_INFO)
    add_feature_info("Library ${name}" _library_enabled "${_extra_text}")
  endif()
  if (NOT _library_enabled)
      return()
  endif()

  # TODO copied from extend_cobot_tp_target.
  # Instead require CMake 3.11 and use extend_cobot_tp_target for setting SOURCES.
  # Requiring cmake 3.11 is necessary because before that add_library requires
  # at least one source file.
  if (_arg_SOURCES_PREFIX)
    foreach(source IN LISTS _arg_SOURCES)
      list(APPEND prefixed_sources "${_arg_SOURCES_PREFIX}/${source}")
      message("${_arg_SOURCES_PREFIX}/${source}")
    endforeach()

    if (NOT IS_ABSOLUTE ${_arg_SOURCES_PREFIX})
      set(_arg_SOURCES_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/${_arg_SOURCES_PREFIX}")
    endif()
    set(_arg_SOURCES ${prefixed_sources})
  endif()

  check_source_files_is_exit(${name} "${_arg_SOURCES}")

  set(library_type SHARED)
  if (_arg_STATIC)
    set(library_type STATIC)
  endif()

  if (_arg_OBJECT)
    set(library_type OBJECT)
  endif()

  set(UI_FILES ${_arg_SOURCES})
  list(FILTER UI_FILES INCLUDE REGEX ".*\\.ui$")
  if(TARGET Qt6::Core)
    qt6_wrap_ui(UI_HEADERS ${UI_FILES})
  else()
    qt5_wrap_ui(UI_HEADERS ${UI_FILES})
  endif()

  add_library(${name} ${library_type} ${_arg_SOURCES} ${UI_HEADERS})

  add_public_headers(${name} "${_arg_SOURCES}")
  # transitional qmake plugin build support
  string(TOLOWER "${name}" lowername)

  set(dependencies_pri "${CMAKE_CURRENT_SOURCE_DIR}/${lowername}_dependencies.pri")

  if(EXISTS ${dependencies_pri})
    message("find ${lowername}_dependencies.pri")
    cobot_tp_add_public_header(${dependencies_pri})
  endif()

  # TODO remove, see above
  if (_arg_SOURCES_PREFIX)
    target_include_directories(${name} PRIVATE $<BUILD_INTERFACE:${_arg_SOURCES_PREFIX}>)
  endif()

  if (${name} MATCHES "^[^0-9-]+$")
    string(TOUPPER "${name}_LIBRARY" EXPORT_SYMBOL)
  endif()

  if(_arg_STATIC AND UNIX)
    # not added by inocobottp if reduce_relocations is turned off for it
    set_target_properties(${name} PROPERTIES POSITION_INDEPENDENT_CODE ON)
  endif()

  extend_cobot_tp_target(${name}
    INCLUDES ${_arg_INCLUDES}
    PUBLIC_INCLUDES ${_arg_PUBLIC_INCLUDES}
    DEFINES ${EXPORT_SYMBOL} ${global_defines_copy} ${_arg_DEFINES} ${TEST_DEFINES}
    PUBLIC_DEFINES ${_arg_PUBLIC_DEFINES}
    DEPENDS ${_arg_DEPENDS} ${IMPLICIT_DEPENDS}
    PUBLIC_DEPENDS ${_arg_PUBLIC_DEPENDS}
    EXPLICIT_MOC ${_arg_EXPLICIT_MOC}
    SKIP_AUTOMOC ${_arg_SKIP_AUTOMOC}
    EXTRA_TRANSLATIONS ${_arg_EXTRA_TRANSLATIONS}
  )

  # everything is different with SOURCES_PREFIX
  if (NOT _arg_SOURCES_PREFIX)
    get_filename_component(public_build_interface_dir "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
    file(RELATIVE_PATH include_dir_relative_path ${PROJECT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/..")
    target_include_directories(${name}
      PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
      PUBLIC
        "$<BUILD_INTERFACE:${public_build_interface_dir}>"
        "$<INSTALL_INTERFACE:${COBOT_TP_HEADER_INSTALL_PATH}/${include_dir_relative_path}>"
    )
  endif()

  set(skip_translation OFF)
  if (_arg_SKIP_TRANSLATION)
    set(skip_translation ON)
  endif()

  set(_DESTINATION "${COBOT_TP_BIN_PATH}")

  if (_arg_DESTINATION)
    set(_DESTINATION "${_arg_DESTINATION}")
  endif()

  set(_output_binary_dir ${PROJECT_BINARY_DIR})
  if(COBOT_ANDROID AND CUSTOM_DEPLOY_ANDROID)
      set(LIB_OUTPUT_PATH ${SO_OUTPUT_PATH})
  else()
      set(LIB_OUTPUT_PATH ${COBOT_TP_LIBRARY_PATH})
  endif()
  # string(REGEX MATCH "^[0-9]*" COBOT_TPVERSION_MAJOR ${COBOT_TPVERSION})
  set_target_properties(${name} PROPERTIES
    LINK_DEPENDS_NO_SHARED ON
    SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    VERSION "${COBOT_TPVERSION}"
    # SOVERSION "${COBOT_TPVERSION_MAJOR}"
    MACHO_CURRENT_VERSION ${COBOT_TPVERSION}
    MACHO_COMPATIBILITY_VERSION ${COBOT_TPVERSION_COMPAT}
    CXX_EXTENSIONS OFF
    CXX_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN ON
    BUILD_RPATH "${_LIB_RPATH}"
    INSTALL_RPATH "${_LIB_RPATH}"
    RUNTIME_OUTPUT_DIRECTORY "${LIB_OUTPUT_PATH}"
    LIBRARY_OUTPUT_DIRECTORY "${LIB_OUTPUT_PATH}"
    ARCHIVE_OUTPUT_DIRECTORY "${COBOT_TP_LIBRARY_ARCHIVE_PATH}"
    ${_arg_PROPERTIES}
  )


  unset(NAMELINK_OPTION)

  if (library_type STREQUAL "SHARED")
    set(NAMELINK_OPTION NAMELINK_SKIP)
  endif()

  unset(COMPONENT_OPTION)

  if (_arg_COMPONENT)
    set(COMPONENT_OPTION "COMPONENT" "${_arg_COMPONENT}")
  endif()

  install(TARGETS ${name}
    EXPORT InoCobotTP
    RUNTIME
      DESTINATION "${_DESTINATION}"
      ${COMPONENT_OPTION}
      OPTIONAL
    LIBRARY
      DESTINATION "${COBOT_TP_LIBRARY_PATH}"
      ${NAMELINK_OPTION}
      ${COMPONENT_OPTION}
      OPTIONAL
    OBJECTS
      DESTINATION "${COBOT_TP_LIBRARY_PATH}"
      COMPONENT Devel EXCLUDE_FROM_ALL
    ARCHIVE
      DESTINATION "${COBOT_TP_LIBRARY_ARCHIVE_PATH}"
      COMPONENT Devel EXCLUDE_FROM_ALL
      OPTIONAL)

  cobot_tp_enable_separate_debug_info(${name} "${COBOT_TP_LIBRARY_PATH}")

  if (NAMELINK_OPTION)
    install(TARGETS ${name}
      LIBRARY
        DESTINATION "${COBOT_TP_LIBRARY_PATH}"
        NAMELINK_ONLY
        COMPONENT Devel EXCLUDE_FROM_ALL
      OPTIONAL
    )
  endif()
endfunction(fun_add_cobot_tp_library)

function(fun_add_cobot_tp_plugin target_name)
  cmake_parse_arguments(_arg
    "SKIP_DEBUG_CMAKE_FILE_CHECK;SKIP_INSTALL;INTERNAL_ONLY;SKIP_TRANSLATION;EXPORT"
    "VERSION;COMPAT_VERSION;PLUGIN_JSON_IN;PLUGIN_PATH;PLUGIN_NAME;OUTPUT_NAME;BUILD_DEFAULT"
    "CONDITION;DEPENDS;PUBLIC_DEPENDS;DEFINES;PUBLIC_DEFINES;INCLUDES;PUBLIC_INCLUDES;SOURCES;EXPLICIT_MOC;SKIP_AUTOMOC;EXTRA_TRANSLATIONS;PLUGIN_DEPENDS;PLUGIN_RECOMMENDS;PLUGIN_TEST_DEPENDS;PROPERTIES"
    ${ARGN}
  )
  if (${_arg_UNPARSED_ARGUMENTS})
    message(FATAL_ERROR "Error! Unparsed arguments in function <fun_add_cobot_tp_plugin>!")
  endif()

  refresh_global_cache(__COBOT_PLUGINS "${target_name}")

  set(name ${target_name})
  if (_arg_PLUGIN_NAME)
    set(name ${_arg_PLUGIN_NAME})
  endif()

  condition_info(_extra_text _arg_CONDITION)
  if (NOT _arg_CONDITION)
    set(_arg_CONDITION ON)
  endif()

  string(TOUPPER "BUILD_PLUGIN_${target_name}" _build_plugin_var)
  if (DEFINED _arg_BUILD_DEFAULT)
    set(_build_plugin_default ${_arg_BUILD_DEFAULT})
  else()
    set(_build_plugin_default ${BUILD_PLUGINS_BY_DEFAULT})
  endif()
  if (DEFINED ENV{InoCobot_${_build_plugin_var}})
    set(_build_plugin_default "$ENV{InoCobot_${_build_plugin_var}}")
  endif()
  if (_arg_INTERNAL_ONLY)
    set(${_build_plugin_var} "${_build_plugin_default}")
  else()
    set(${_build_plugin_var} "${_build_plugin_default}" CACHE BOOL "Build plugin ${name}.")
  endif()

  if ((${_arg_CONDITION}) AND ${_build_plugin_var})
    set(_plugin_enabled ON)
  else()
    set(_plugin_enabled OFF)
  endif()

  if (NOT _arg_INTERNAL_ONLY)
    add_feature_info("Plugin ${name}" _plugin_enabled "${_extra_text}")
  endif()
  if (NOT _plugin_enabled)
    return()
  endif()

  ### Generate plugin.json file:
  if (NOT _arg_VERSION)
    set(_arg_VERSION ${COBOT_TPVERSION})
  endif()
  if (NOT _arg_COMPAT_VERSION)
    set(_arg_COMPAT_VERSION ${_arg_VERSION})
  endif()

  if (NOT _arg_SKIP_DEBUG_CMAKE_FILE_CHECK)
    check_source_files_is_exit(${target_name} "${_arg_SOURCES}")
  endif()

  # Generate dependency list:
  find_dependent_plugins(_DEP_PLUGINS ${_arg_PLUGIN_DEPENDS})

  set(_arg_DEPENDENCY_STRING "\"Dependencies\" : [\n")
  foreach(i IN LISTS _DEP_PLUGINS)
    get_property(_v TARGET "${i}" PROPERTY _arg_VERSION)
    string(APPEND _arg_DEPENDENCY_STRING
      "        { \"Name\" : \"${i}\", \"Version\" : \"${_v}\" }"
    )
  endforeach(i)
  foreach(i IN LISTS _arg_PLUGIN_RECOMMENDS)
      get_property(_v TARGET "${i}" PROPERTY _arg_VERSION)
    string(APPEND _arg_DEPENDENCY_STRING
      "        { \"Name\" : \"${i}\", \"Version\" : \"${_v}\", \"Type\" : \"optional\" }"
    )
  endforeach(i)
  foreach(i IN LISTS _arg_PLUGIN_TEST_DEPENDS)
    set(_v ${COBOT_TPVERSION})
    string(APPEND _arg_DEPENDENCY_STRING
      "        { \"Name\" : \"${i}\", \"Version\" : \"${_v}\", \"Type\" : \"test\" }"
    )
  endforeach(i)

  string(REPLACE "}        {" "},\n        {"
    _arg_DEPENDENCY_STRING "${_arg_DEPENDENCY_STRING}"
  )
  string(APPEND _arg_DEPENDENCY_STRING "\n    ]")

  set(COBOT_TPPLUGIN_DEPENDENCY_STRING ${_arg_DEPENDENCY_STRING})

  ### Configure plugin.json file:
  string(TOLOWER ${name} lower_json_name)
  if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${lower_json_name}.json.in")
    set(json_file_name "${CMAKE_CURRENT_SOURCE_DIR}/${lower_json_name}.json.in")
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${name}.json.in")
    set(json_file_name "${CMAKE_CURRENT_SOURCE_DIR}/${name}.json.in")
  else()
    message(FATAL_ERROR "Json file does't exit. Plugin name is ${name}")
  endif()

  file(READ "${json_file_name}" plugin_json_in)
  string(REPLACE "\\\"" "\"" plugin_json_in ${plugin_json_in})
  string(REPLACE "\\'" "'" plugin_json_in ${plugin_json_in})
  string(REPLACE "$$COBOT_TP_PLUGIN_NAME" "\${target_name}" plugin_json_in ${plugin_json_in})
  string(REPLACE "$$COBOT_TP_VERSION" "\${_arg_VERSION}" plugin_json_in ${plugin_json_in})
  string(REPLACE "$$COBOT_TP_COMPAT_VERSION" "\${_arg_COMPAT_VERSION}" plugin_json_in ${plugin_json_in})
  string(REPLACE "$$dependencyList" "\${COBOT_TPPLUGIN_DEPENDENCY_STRING}" plugin_json_in ${plugin_json_in})
  if(_arg_PLUGIN_JSON_IN)
    string(REGEX REPLACE "=.*$" "" json_key ${_arg_PLUGIN_JSON_IN})
    string(REGEX REPLACE "^.*=" "" json_value ${_arg_PLUGIN_JSON_IN})
    string(REPLACE "$$${json_key}" "${json_value}" plugin_json_in ${plugin_json_in})
  endif()
  string(CONFIGURE "${plugin_json_in}" plugin_json)
  file(GENERATE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${name}.json"
    CONTENT "${plugin_json}")

  set(UI_FILES ${_arg_SOURCES})
  list(FILTER UI_FILES INCLUDE REGEX ".*\\.ui$")

  if(TARGET Qt6::Core)
    qt6_wrap_ui(UI_HEADERS ${UI_FILES})
  else()
    qt5_wrap_ui(UI_HEADERS ${UI_FILES})
  endif()


  add_library(${target_name} SHARED ${_arg_SOURCES} ${UI_HEADERS})

  if(COBOT_ANDROID)
      set(COBOT_TP_PLUGIN_LIST
          ${target_name} ${COBOT_TP_PLUGIN_LIST}
          CACHE INTERNAL "COBOT_TP_PLUGIN_LIST" FORCE)#
  endif()
  add_public_headers(${target_name} "${_arg_SOURCES}")
  # transitional qmake plugin build support
  string(TOLOWER "${target_name}" lowername)
  set(dependencies_pri "${CMAKE_CURRENT_SOURCE_DIR}/${lowername}_dependencies.pri")
  # if(EXISTS ${dependencies_pri})
  #   cobot_tp_add_public_header(${dependencies_pri})
  # endif()

  ### Generate EXPORT_SYMBOL
  string(TOUPPER "${name}_LIBRARY" EXPORT_SYMBOL)

  list(APPEND _arg_DEFINES COBOT_TP_PLUGIN_JSON_FILE_NAME="${CMAKE_CURRENT_BINARY_DIR}/${target_name}.json")
  list(APPEND _arg_DEFINES COBOT_TP_PLUGIN_NAME="${target_name}")

  extend_cobot_tp_target(${target_name}
    INCLUDES ${_arg_INCLUDES}
    PUBLIC_INCLUDES ${_arg_PUBLIC_INCLUDES}
    DEFINES ${EXPORT_SYMBOL} ${GLOBAL_DEFINES} ${_arg_DEFINES} ${TEST_DEFINES}
    PUBLIC_DEFINES ${_arg_PUBLIC_DEFINES}
    DEPENDS ${_arg_DEPENDS} ${_DEP_PLUGINS} ${IMPLICIT_DEPENDS}
    PUBLIC_DEPENDS ${_arg_PUBLIC_DEPENDS}
    EXPLICIT_MOC ${_arg_EXPLICIT_MOC}
    SKIP_AUTOMOC ${_arg_SKIP_AUTOMOC}
    EXTRA_TRANSLATIONS ${_arg_EXTRA_TRANSLATIONS}
  )

  get_filename_component(public_build_interface_dir "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
  file(RELATIVE_PATH include_dir_relative_path ${PROJECT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/..")
  target_include_directories(${target_name}
    PRIVATE
      "${CMAKE_CURRENT_BINARY_DIR}"
      "${CMAKE_BINARY_DIR}/src"
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    PUBLIC
      "$<BUILD_INTERFACE:${public_build_interface_dir}>"
      "$<INSTALL_INTERFACE:${COBOT_TP_HEADER_INSTALL_PATH}/${include_dir_relative_path}>"
  )

  set(plugin_dir "${COBOT_TPPLUGIN_PATH}")
  if (_arg_PLUGIN_PATH)
    set(plugin_dir "${_arg_PLUGIN_PATH}")
  endif()

  set(skip_translation OFF)
  if (_arg_SKIP_TRANSLATION)
    set(skip_translation ON)
  endif()
  set(_output_binary_dir ${PROJECT_BINARY_DIR})
  if(COBOT_ANDROID AND CUSTOM_DEPLOY_ANDROID)
      set(PLUGIN_OUTPUT_PATH ${SO_OUTPUT_PATH})
  else()
      set(PLUGIN_OUTPUT_PATH ${COBOT_TP_PLUGIN_PATH})
  endif()
  set_target_properties(${target_name} PROPERTIES
    LINK_DEPENDS_NO_SHARED ON
    SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    MACHO_CURRENT_VERSION ${COBOT_TPVERSION}
    MACHO_COMPATIBILITY_VERSION ${COBOT_TPVERSION_COMPAT}
    CXX_EXTENSIONS OFF
    CXX_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN ON
    _arg_DEPENDS "${_arg_PLUGIN_DEPENDS}"
    _arg_VERSION "${_arg_VERSION}"
    BUILD_RPATH "${_PLUGIN_RPATH}"
    INSTALL_RPATH "${_PLUGIN_RPATH}"
    # BUILD_RPATH "${_PLUGIN_BULID_RPATH}"
    # INSTALL_RPATH "${_PLUGIN_RUN_RPATH}"
    LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}"
    ARCHIVE_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}"
    OUTPUT_NAME "${name}"
    COBOTSKIP_TRANSLATION "${skip_translation}"
    ${_arg_PROPERTIES}
  )


  if (NOT _arg_SKIP_INSTALL)
    if (_arg_EXPORT)
      set(export COBOT${target_name})
    else()
      set(export COBOT)
    endif()

    install(TARGETS ${target_name}
      EXPORT ${export}
      RUNTIME DESTINATION "${plugin_dir}" OPTIONAL
      LIBRARY DESTINATION "${plugin_dir}" OPTIONAL
      ARCHIVE
        DESTINATION "${plugin_dir}"
        COMPONENT Devel EXCLUDE_FROM_ALL
        OPTIONAL
    )

    cobot_tp_enable_separate_debug_info(${target_name} "${plugin_dir}")

    if (_arg_EXPORT)
      # export of external plugins
      install(EXPORT ${export}
        FILE ${export}Targets.cmake
        DESTINATION ${COBOT_TP_CMAKE_INSTALL_PATH}/${export}
        COMPONENT Devel EXCLUDE_FROM_ALL
        NAMESPACE InoCobotTP::
      )
      include(CMakePackageConfigHelpers)
      configure_package_config_file(${_THIS_MODULE_BASE_DIR}/Config.cmake.in
        "${CMAKE_BINARY_DIR}/cmake/${export}Config.cmake"
        INSTALL_DESTINATION ${COBOT_TP_CMAKE_INSTALL_PATH}/${export}
      )
      install(
        FILES ${CMAKE_BINARY_DIR}/cmake/${export}Config.cmake
        DESTINATION ${COBOT_TP_CMAKE_INSTALL_PATH}/${export}
        COMPONENT Devel EXCLUDE_FROM_ALL
      )
      export(EXPORT ${export}
        NAMESPACE InoCobotTP::
        FILE ${CMAKE_BINARY_DIR}/cmake/${export}Targets.cmake
      )
    endif()
  endif()
endfunction()

function(extend_cobot_tp_plugin target_name)
  cobot_tp_plugin_enabled(_plugin_enabled ${target_name})
  if (NOT _plugin_enabled)
    return()
  endif()

  extend_cobot_tp_target(${target_name} ${ARGN})
endfunction()

function(extend_cobot_tp_library target_name)
  cobot_tp_library_enabled(_library_enabled ${target_name})
  if (NOT _library_enabled)
    return()
  endif()

  extend_cobot_tp_target(${target_name} ${ARGN})
endfunction()

function(extend_cobot_tp_test target_name)
  if (NOT (target_name IN_LIST __COBOT_TESTS))
    message(FATAL_ERROR "extend_cobot_tp_test: Unknown test target \"${target_name}\"")
  endif()
  if (TARGET ${target_name})
    extend_cobot_tp_target(${target_name} ${ARGN})
  endif()
endfunction()

function(add_cobot_tp_executable name)
  cmake_parse_arguments(_arg "SKIP_INSTALL;SKIP_TRANSLATION;ALLOW_ASCII_CASTS;INOCOBOTTP_RUNNABLE"
    "DESTINATION;COMPONENT;BUILD_DEFAULT"
    "CONDITION;DEPENDS;DEFINES;INCLUDES;SOURCES;EXPLICIT_MOC;SKIP_AUTOMOC;EXTRA_TRANSLATIONS;PROPERTIES" ${ARGN})

  if (${_arg_UNPARSED_ARGUMENTS})
    message(FATAL_ERROR "Error! Unparsed arguments in function <add_cobot_tp_executable>!")
  endif()

  set(global_defines_copy ${GLOBAL_DEFINES})

  refresh_global_cache(__COBOT_EXECUTABLES "${name}")

  if (NOT _arg_CONDITION)
    set(_arg_CONDITION ON)
  endif()

  string(TOUPPER "BUILD_EXECUTABLE_${name}" _build_executable_var)
  if (DEFINED _arg_BUILD_DEFAULT)
    set(_build_executable_default ${_arg_BUILD_DEFAULT})
  else()
    set(_build_executable_default ${BUILD_EXECUTABLES_BY_DEFAULT})
  endif()
  if (DEFINED ENV{InoCobotTP_${_build_executable_var}})
    set(_build_executable_default "$ENV{InoCobotTP_${_build_executable_var}}")
  endif()
  set(${_build_executable_var} "${_build_executable_default}" CACHE BOOL "Build executable ${name}.")

  if ((${_arg_CONDITION}) AND ${_build_executable_var})
    set(_executable_enabled ON)
  else()
    set(_executable_enabled OFF)
  endif()
  if (NOT _executable_enabled)
    return()
  endif()

  set(_DESTINATION "${COBOT_TP_APP_PATH}")
  if (_arg_DESTINATION)
    set(_DESTINATION "${_arg_DESTINATION}")
  endif()
  set(_EXECUTABLE_PATH "${_DESTINATION}")

  if(COBOT_ANDROID)
      if(CUSTOM_DEPLOY_ANDROID)
          set(COBOT_TP_PLUGIN_LIST)
          add_library(${name} SHARED ${_arg_SOURCES})
      else()
          set(InoCobot_plugin_depends ${COBOT_TP_PLUGIN_LIST})
          qt_add_executable("${name}" MANUAL_FINALIZATION ${_arg_SOURCES})
          # cobot_tp_add_executable("${name}" MANUAL_FINALIZATION ${_arg_SOURCES})
      endif()
  else()
      add_executable("${name}" ${_arg_SOURCES})
  endif()

  extend_cobot_tp_target("${name}"
    INCLUDES "${CMAKE_BINARY_DIR}/src" ${_arg_INCLUDES}
    DEFINES ${global_defines_copy} ${TEST_DEFINES} ${_arg_DEFINES}
    DEPENDS ${_arg_DEPENDS} ${IMPLICIT_DEPENDS} ${COBOT_TP_PLUGIN_LIST}
    EXPLICIT_MOC ${_arg_EXPLICIT_MOC}
    SKIP_AUTOMOC ${_arg_SKIP_AUTOMOC}
    EXTRA_TRANSLATIONS ${_arg_EXTRA_TRANSLATIONS}
  )

  set(skip_translation OFF)
  if (_arg_SKIP_TRANSLATION)
    set(skip_translation ON)
  endif()

  if(WIN32)
    file(RELATIVE_PATH relative_lib_path "/${_EXECUTABLE_PATH}" "/${COBOT_TP_LIBRARY_PATH}")
    set(build_rpath "${_RPATH_BASE}/${relative_lib_path}")
    set(install_rpath "${_RPATH_BASE}/${relative_lib_path}")

    set(OUTPUT_APP_NAME "${name}")
    set(APP_PATH ${COBOT_TP_APP_PATH})
  elseif (COBOT_ANDROID)
    if(CUSTOM_DEPLOY_ANDROID)
        set(build_rpath)
        set(install_rpath)

        set(OUTPUT_APP_NAME "${name}_${COBOT_TP_ANDROID_ABI}")
        set(APP_PATH ${SO_OUTPUT_PATH})
        message("SO_OUTPUT_PATH is ${SO_OUTPUT_PATH}  ")
    else()
      file(RELATIVE_PATH build_rpath  ${COBOT_TP_LIBRARY_PATH} ${COBOT_TP_APP_PATH})
      file(RELATIVE_PATH install_rpath  ${COBOT_TP_APP_PATH} ${COBOT_TP_APP_PATH})
      file(RELATIVE_PATH library_rpath  ${COBOT_TP_APP_PATH} ${COBOT_TP_LIBRARY_PATH})
      file(RELATIVE_PATH plugin_rpath  ${COBOT_TP_APP_PATH} ${COBOT_TP_PLUGIN_PATH})
      set(install_rpath "${install_rpath};${library_rpath};${plugin_rpath}")

      set(OUTPUT_APP_NAME "${name}")
      set(APP_PATH ${COBOT_TP_APP_PATH})
    endif()
  endif()

  # if(CUSTOM_DEPLOY_ANDROID)
  #     set(OUTPUT_APP_NAME "${name}_${COBOT_TP_ANDROID_ABI}")
  #     set(APP_PATH ${SO_OUTPUT_PATH})
  #     message("SO_OUTPUT_PATH is ${SO_OUTPUT_PATH}  ")
  # else()
  #     set(OUTPUT_APP_NAME "${name}")
  #     set(APP_PATH ${COBOT_TP_APP_PATH})
  # endif()
  set(_output_binary_dir ${CMAKE_BINARY_DIR})
  set_target_properties("${name}" PROPERTIES
    LINK_DEPENDS_NO_SHARED ON
    BUILD_RPATH "${build_rpath}"
    INSTALL_RPATH "${install_rpath}"
    RUNTIME_OUTPUT_DIRECTORY "${APP_PATH}"
    COBOTSKIP_TRANSLATION "${skip_translation}"
    CXX_EXTENSIONS OFF
    CXX_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN ON
    OUTPUT_NAME ${OUTPUT_APP_NAME}
    ${_arg_PROPERTIES} )

  if (_arg_INOCOBOTTP_RUNNABLE)
      #select the default target in the project
      set_target_properties(${name} PROPERTIES FOLDER "cobot_tp_runnable")
  endif()

  if (NOT _arg_SKIP_INSTALL)
    unset(COMPONENT_OPTION)
    if (_arg_COMPONENT)
      set(COMPONENT_OPTION "COMPONENT" "${_arg_COMPONENT}")
    endif()

    cobot_tp_enable_separate_debug_info(${name} "${_DESTINATION}")
  endif()

endfunction()

function(extend_cobot_tp_executable name)
  if (NOT (name IN_LIST __COBOT_EXECUTABLES))
    message(FATAL_ERROR "extend_cobot_tp_executable: Unknown executable target \"${name}\"")
  endif()
  if (TARGET ${name})
    extend_cobot_tp_target(${name} ${ARGN})
  endif()
endfunction()

function(cobot_tp_copy_to_builddir custom_target_name)
  cmake_parse_arguments(_arg "CREATE_SUBDIRS" "DESTINATION" "FILES;DIRECTORIES" ${ARGN})
  set(timestampFiles)
  set(_output_binary_dir ${PROJECT_BINARY_DIR})
  set(allFiles ${_arg_FILES})

  foreach(srcFile ${_arg_FILES})
    string(MAKE_C_IDENTIFIER "${srcFile}" destinationTimestampFilePart)
    set(destinationTimestampFileName "${CMAKE_CURRENT_BINARY_DIR}/.${destinationTimestampFilePart}_timestamp")
    list(APPEND timestampFiles "${destinationTimestampFileName}")

    if (IS_ABSOLUTE "${srcFile}")
      set(srcPath "")
    else()
      get_filename_component(srcPath "${srcFile}" DIRECTORY)
    endif()

    add_custom_command(OUTPUT "${destinationTimestampFileName}"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${_output_binary_dir}/${_arg_DESTINATION}/${srcPath}"
      COMMAND "${CMAKE_COMMAND}" -E copy "${srcFile}" "${_output_binary_dir}/${_arg_DESTINATION}/${srcPath}"
      COMMAND "${CMAKE_COMMAND}" -E touch "${destinationTimestampFileName}"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      COMMENT "Copy ${srcFile} into build directory"
      DEPENDS "${srcFile}"
      VERBATIM)
  endforeach()

  foreach(srcDirectory ${_arg_DIRECTORIES})
    string(MAKE_C_IDENTIFIER "${srcDirectory}" destinationTimestampFilePart)
    set(destinationTimestampFileName "${CMAKE_CURRENT_BINARY_DIR}/.${destinationTimestampFilePart}_timestamp")
    list(APPEND timestampFiles "${destinationTimestampFileName}")
    set(destinationDirectory "${_output_binary_dir}/${_arg_DESTINATION}")

    if(_arg_CREATE_SUBDIRS)
      set(destinationDirectory "${destinationDirectory}/${srcDirectory}")
    endif()

    file(GLOB_RECURSE filesToCopy "${srcDirectory}/*")
    list(APPEND allFiles ${filesToCopy})
    add_custom_command(OUTPUT "${destinationTimestampFileName}"
      COMMAND "${CMAKE_COMMAND}" -E copy_directory "${srcDirectory}" "${destinationDirectory}"
      COMMAND "${CMAKE_COMMAND}" -E touch "${destinationTimestampFileName}"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      COMMENT "Copy ${srcDirectory}/ into build directory"
      DEPENDS ${filesToCopy}
      VERBATIM)
  endforeach()

  add_custom_target("${custom_target_name}" ALL DEPENDS ${timestampFiles}
    SOURCES ${allFiles})
endfunction()

function(cobot_tp_add_resources target resourceName)
  cmake_parse_arguments(rcc "" "PREFIX;LANG;BASE" "FILES;OPTIONS;CONDITION" ${ARGN})
  if (${_arg_UNPARSED_ARGUMENTS})
    message(FATAL_ERROR "Error! Unparsed arguments in function <cobot_tp_add_resources>!")
  endif()

  if (DEFINED _arg_CONDITION AND NOT _arg_CONDITION)
    return()
  endif()

  if(NOT TARGET ${target})
    return()
  endif()

  string(REPLACE "/" "_" resourceName ${resourceName})
  string(REPLACE "." "_" resourceName ${resourceName})

  # Apply base to all files
  if (rcc_BASE)
    foreach(file IN LISTS rcc_FILES)
      set(resource_file "${rcc_BASE}/${file}")
      file(TO_CMAKE_PATH ${resource_file} resource_file)
      list(APPEND resource_files ${resource_file})
    endforeach()
  else()
      set(resource_files ${rcc_FILES})
  endif()

  set(newResourceName ${resourceName})
  set(resources ${resource_files})

  set(generatedResourceFile "${CMAKE_CURRENT_BINARY_DIR}/.rcc/generated_${newResourceName}.qrc")
  set(generatedSourceCode "${CMAKE_CURRENT_BINARY_DIR}/.rcc/qrc_${newResourceName}.cpp")

  # Generate .qrc file:

  # <RCC><qresource ...>
  set(qrcContents "<RCC>\n  <qresource")
  if (rcc_PREFIX)
      string(APPEND qrcContents " prefix=\"${rcc_PREFIX}\"")
  endif()
  if (rcc_LANG)
      string(APPEND qrcContents " lang=\"${rcc_LANG}\"")
  endif()
  string(APPEND qrcContents ">\n")

  set(resource_dependencies)
  foreach(file IN LISTS resources)
    set(file_resource_path ${file})

    if (NOT IS_ABSOLUTE ${file})
        set(file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    endif()

    ### FIXME: escape file paths to be XML conform
    # <file ...>...</file>
    string(APPEND qrcContents "    <file alias=\"${file_resource_path}\">")
    string(APPEND qrcContents "${file}</file>\n")
    list(APPEND files "${file}")
    list(APPEND resource_dependencies ${file})
    target_sources(${target} PRIVATE "${file}")
    set_property(SOURCE "${file}" PROPERTY HEADER_FILE_ONLY ON)
  endforeach()

  # </qresource></RCC>
  string(APPEND qrcContents "  </qresource>\n</RCC>\n")

  file(WRITE "${generatedResourceFile}.in" "${qrcContents}")
  configure_file("${generatedResourceFile}.in" "${generatedResourceFile}")

  set_property(TARGET ${target} APPEND PROPERTY _inocobottp_generated_qrc_files "${generatedResourceFile}")

  set(rccArgs --name "${newResourceName}"
      --output "${generatedSourceCode}" "${generatedResourceFile}")
  if(rcc_OPTIONS)
      list(APPEND rccArgs ${rcc_OPTIONS})
  endif()
  # 处理 .qrc
  add_custom_command(OUTPUT "${generatedSourceCode}"
                     COMMAND Qt${QT_VERSION_MAJOR}::rcc ${rccArgs}
                     DEPENDS
                      ${resource_dependencies}
                      ${generatedResourceFile}
                      "Qt${QT_VERSION_MAJOR}::rcc"
                     COMMENT "RCC ${newResourceName}"
                     VERBATIM)

  target_sources(${target} PRIVATE "${generatedSourceCode}")
  set_property(SOURCE "${generatedSourceCode}" PROPERTY SKIP_AUTOGEN ON)
  set_property(SOURCE "${generatedResourceFile}.in" PROPERTY SKIP_AUTOGEN ON)
endfunction()

function(cobot_tp_add_public_header header)
  if (NOT IS_ABSOLUTE ${header})
    set(header "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
  endif()
  set(inocobot_source_dir ${PROJECT_SOURCE_DIR})
  get_filename_component(source_dir ${header} DIRECTORY)
  file(RELATIVE_PATH include_dir_relative_path ${inocobot_source_dir} ${source_dir})
  install(
    FILES ${header}
    DESTINATION "${COBOT_TP_HEADER_INSTALL_PATH}/${include_dir_relative_path}"
    COMPONENT Devel EXCLUDE_FROM_ALL
  )
endfunction()

function(update_plugin_dll list_plugin_new)
    set(Plugin_Path_List_New)
    # if(ANDROID)
    #     foreach(Plugin ${list_plugin_new})
    #         set(Lib_Plugin_DLL "lib${Plugin}.so")
    #         set(PluginPath ${COBOT_TP_BIN_PATH}/${Lib_Plugin_DLL})
    #         list(APPEND Plugin_Path_List_New ${PluginPath})
    #     endforeach()

    #     file(GLOB Plugin_Path_List_Old "${COBOT_TP_BIN_PATH}/*.so")
    # endif()
    foreach(Plugin ${list_plugin_new})
        set(Lib_Plugin_DLL "lib${Plugin}.dll")
        set(PluginPath ${COBOT_TP_BIN_PATH}/plugins/${Lib_Plugin_DLL})
        list(APPEND Plugin_Path_List_New ${PluginPath})
    endforeach()

    file(GLOB Plugin_Path_List_Old "${COBOT_TP_BIN_PATH}/plugins/*.dll")
    foreach(Plugin ${Plugin_Path_List_Old})
        list(FIND Plugin_Path_List_New ${Plugin} index)
        if(index EQUAL -1)
            if(EXISTS "${Plugin}")
                file(REMOVE "${Plugin}")
            endif()
            if(EXISTS "${Plugin}.a")
                file(REMOVE "${Plugin}.a")
            endif()
        endif()
    endforeach()
endfunction()

function(list_contains list object result)
    list(FIND list ${object} index)
    if(${index} GREATER -1)
        set(value 1)
    else()
        set(value 0)
    endif()
    set(${result} ${value} PARENT_SCOPE)
endfunction()

function(target_funcMacro_definitions libName mode funcName value)
    list_contains("${__COBOT_LIBRARIES}" ${libName} result)
    if (result)
        target_compile_definitions(${libName} ${mode} -D${funcName}=${value})
    else()
        list_contains("${__COBOT_PLUGINS}" ${libName} result)
        if (result)
            target_compile_definitions(${libName} ${mode} -D${funcName}=${value})
        else()
            if(NOT TEACH_DEMO_TRIMMED)
                message("${libName} is not exist!")
            endif()
        endif()
    endif()
endfunction()
