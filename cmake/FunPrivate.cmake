message("RELATIVE_PLUGIN_PATH is  " ${RELATIVE_PLUGIN_PATH})
message("RELATIVE_SHARE_PATH is  " ${RELATIVE_SHARE_PATH})
message("RELATIVE_SDK_SHARE_PATH is  " ${RELATIVE_SDK_SHARE_PATH})
message("RELATIVE_DEP_LIB_PATH is  " ${RELATIVE_DEP_LIB_PATH})

list(APPEND GLOBAL_DEFINES
    UNICODE
    _UNICODE
    INOROBOT)

if (WIN32)
  list(APPEND GLOBAL_DEFINES
      Q_OS_WIN
      WIN32_LEAN_AND_MEAN)
endif()

if (WIN32)
    set(_RPATH_BASE "")
    set(_LIB_RPATH "")
    set(_PLUGIN_RPATH "")
    set(_APP_DATA_PATH "share/teachpendant")
elseif(COBOT_ANDROID)
    set(_RPATH_BASE "")
    set(_LIB_RPATH "")
    set(_PLUGIN_RPATH "")
    set(_PLUGIN_RUN_RPATH "")
    set(_PLUGIN_BULID_RPATH "/../../../")
    set(_APP_DATA_PATH "share/teachpendant")
endif ()

set(__COBOT_PLUGINS "" CACHE INTERNAL "*** Private ***")
set(__COBOT_LIBRARIES "" CACHE INTERNAL "*** Private ***")
set(__COBOT_EXECUTABLES "" CACHE INTERNAL "*** Private ***")
set(__COBOT_TESTS "" CACHE INTERNAL "*** Private ***")

function(cobot_tp_handle_sccache_support)
  if (MSVC AND WITH_SCCACHE_SUPPORT)
    foreach(config DEBUG RELWITHDEBINFO)
      foreach(lang C CXX)
        set(flags_var "CMAKE_${lang}_FLAGS_${config}")
        string(REPLACE "/Zi" "/Z7" ${flags_var} "${${flags_var}}")
        set(${flags_var} "${${flags_var}}" PARENT_SCOPE)
      endforeach()
    endforeach()
  endif()
endfunction()

function(cobot_tp_enable_release_for_debug_configuration)
  if (MSVC)
    string(REPLACE "/Od" "/O2" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/Ob0" "/Ob1" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/RTC1" ""  CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2")
  endif()
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" PARENT_SCOPE)
endfunction()

function(add_translation_files target_name)
  if(NOT ARGN)
    return()
  endif()

  if(TARGET "${target_name}")
    get_target_property(_input "${target_name}" INOCOBOTTP_EXTRA_TRANSLATIONS)
    if (_input)
      set(_output "${_input}" "${ARGN}")
    else()
      set(_output "${ARGN}")
    endif()
    set_target_properties("${target_name}" PROPERTIES INOCOBOTTP_EXTRA_TRANSLATIONS "${_output}")
  endif()
endfunction()

function(refresh_global_cache name value)
  set(_tmp_list "${${name}}")
  list(APPEND _tmp_list "${value}")
  set("${name}" "${_tmp_list}" CACHE INTERNAL "*** Internal ***")
endfunction()

function(check_source_files_is_exit target_name sources)
  if(NOT WITH_DEBUG_CMAKE)
    return()
  endif()
  file(GLOB_RECURSE files RELATIVE ${CMAKE_CURRENT_LIST_DIR}
        "*.cpp" "*.hpp" "*.c" "*.h" "*.ui" "*.qrc")

  #检查遗漏文件
  foreach(file IN LISTS files)
    if(NOT ${file} IN_LIST sources)
      message(STATUS "${file} won't be complie beacuse ${target_name} project doesn't contains it")
    endif()
  endforeach()

  foreach(source IN LISTS "${sources}")
    if(NOT ${source} IN_LIST files)
      message(STATUS "${source} does't contains in project ${target_name}")
    endif()
  endforeach()
endfunction(check_source_files_is_exit)

function(separate_object_libraries libraries REGULAR_LIBS OBJECT_LIBS OBJECT_LIB_OBJECTS)
  set(${REGULAR_LIBS} ${libraries} PARENT_SCOPE)
  unset(${OBJECT_LIBS} PARENT_SCOPE)
  unset(${OBJECT_LIB_OBJECTS} PARENT_SCOPE)
endfunction(separate_object_libraries)

function(set_explicit_moc target_name file)
  unset(file_dependencies)
  if (file MATCHES "^.*plugin.h$")
    set(file_dependencies DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${target_name}.json")
  endif()
  set_property(SOURCE "${file}" PROPERTY SKIP_AUTOMOC ON)
  if(TARGET Qt6::Core)
    qt6_wrap_cpp(file_moc "${file}" ${file_dependencies})
  else()
    qt5_wrap_cpp(file_moc "${file}" ${file_dependencies})
  endif()
 
  target_sources(${target_name} PRIVATE "${file_moc}")
endfunction()

function(add_public_headers target sources)
  foreach(source IN LISTS sources)
    if (source MATCHES "\.h$|\.hpp$")
      cobot_tp_add_public_header(${source})
    endif()
  endforeach()
endfunction()

function(add_public_includes target includes)
  foreach(inc_dir IN LISTS includes)
    if (NOT IS_ABSOLUTE ${inc_dir})
      set(inc_dir "${CMAKE_CURRENT_SOURCE_DIR}/${inc_dir}")
    endif()
    file(RELATIVE_PATH include_dir_relative_path ${PROJECT_SOURCE_DIR} ${inc_dir})
    target_include_directories(${target} PUBLIC
      $<BUILD_INTERFACE:${inc_dir}>
      $<INSTALL_INTERFACE:${COBOT_TP_HEADER_INSTALL_PATH}/${include_dir_relative_path}>
    )
  endforeach()
endfunction()

function(finalize_test_setup test_name)
  cmake_parse_arguments(_arg "" "TIMEOUT" "" ${ARGN})
  if (DEFINED _arg_TIMEOUT)
    set(timeout ${_arg_TIMEOUT})
  else()
    set(timeout 5)
  endif()
  # Never translate tests:
  set_tests_properties(${name}
    PROPERTIES
      COBOTSKIP_TRANSLATION ON
      TIMEOUT ${timeout}
  )

  if (WIN32)
    list(APPEND env_path $ENV{PATH})
    list(APPEND env_path ${CMAKE_BINARY_DIR}/${COBOT_TP_PLUGIN_PATH})
    list(APPEND env_path ${CMAKE_BINARY_DIR}/${COBOT_TP_BIN_PATH})
    list(APPEND env_path $<TARGET_FILE_DIR:InoCobotTP::Test>)
    if (TARGET libclang)
        list(APPEND env_path $<TARGET_FILE_DIR:libclang>)
    endif()

    if (TARGET elfutils::elf)
        list(APPEND env_path $<TARGET_FILE_DIR:elfutils::elf>)
    endif()

    string(REPLACE "/" "\\" env_path "${env_path}")
    string(REPLACE ";" "\\;" env_path "${env_path}")

    set_tests_properties(${test_name} PROPERTIES ENVIRONMENT "PATH=${env_path}")
  endif()
endfunction()

function(check_cobot_tp_disabled_targets target_name dependent_targets)
  foreach(dependency IN LISTS ${dependent_targets})
    foreach(type PLUGIN LIBRARY)
      string(TOUPPER "BUILD_${type}_${dependency}" build_target)
      if (DEFINED ${build_target} AND NOT ${build_target})
        message(SEND_ERROR "Target ${name} depends on ${dependency} which was disabled via ${build_target} set to ${${build_target}}")
      endif()
    endforeach()
  endforeach()
endfunction()

function(add_cobot_tp_depends target_name)
  cmake_parse_arguments(_arg "" "" "PRIVATE;PUBLIC" ${ARGN})
  if (${_arg_UNPARSED_ARGUMENTS})
    message(FATAL_ERROR "Error! Unparsed arguments in function <add_cobot_tp_depends>!")
  endif()
  check_cobot_tp_disabled_targets(${target_name} _arg_PRIVATE)
  check_cobot_tp_disabled_targets(${target_name} _arg_PUBLIC)
  separate_object_libraries("${_arg_PRIVATE}"
    depends object_lib_depends object_lib_depends_objects)
  separate_object_libraries("${_arg_PUBLIC}"
    public_depends object_public_depends object_public_depends_objects)

  target_sources(${target_name} PRIVATE ${object_lib_depends_objects} ${object_public_depends_objects})

  get_target_property(target_type ${target_name} TYPE)
  if (NOT target_type STREQUAL "OBJECT_LIBRARY")
    target_link_libraries(${target_name} PRIVATE ${depends} PUBLIC ${public_depends})
  else()
    list(APPEND object_lib_depends ${depends})
    list(APPEND object_public_depends ${public_depends})
  endif()


  foreach(item IN LISTS object_lib_depends)
    target_compile_options(${target_name} PRIVATE $<TARGET_PROPERTY:${item},INTERFACE_COMPILE_OPTIONS>)
    target_compile_definitions(${target_name} PRIVATE $<TARGET_PROPERTY:${item},INTERFACE_COMPILE_DEFINITIONS>)
    target_include_directories(${target_name} PRIVATE $<TARGET_PROPERTY:${item},INTERFACE_INCLUDE_DIRECTORIES>)
  endforeach()
  foreach(item IN LISTS object_public_depends)
    target_compile_options(${target_name} PUBLIC $<TARGET_PROPERTY:${item},INTERFACE_COMPILE_OPTIONS>)
    target_compile_definitions(${target_name} PUBLIC $<TARGET_PROPERTY:${item},INTERFACE_COMPILE_DEFINITIONS>)
    target_include_directories(${target_name} PUBLIC $<TARGET_PROPERTY:${item},INTERFACE_INCLUDE_DIRECTORIES>)
  endforeach()
endfunction()


function(find_dependent_plugins varName)
  set(_RESULT ${ARGN})
  foreach(i ${ARGN})
    get_property(_dep TARGET "${i}" PROPERTY _arg_DEPENDS)
    if (_dep)
      find_dependent_plugins(_REC ${_dep})
      list(APPEND _RESULT ${_REC})
    endif()
  endforeach()

  if (_RESULT)
    list(REMOVE_DUPLICATES _RESULT)
    list(SORT _RESULT)
  endif()

  set("${varName}" ${_RESULT} PARENT_SCOPE)
endfunction()


function(condition_info varName condition)
  if (NOT ${condition})
    set(${varName} "" PARENT_SCOPE)
  else()
    string(REPLACE ";" " " _contents "${${condition}}")
    set(${varName} "with CONDITION ${_contents}" PARENT_SCOPE)
  endif()
endfunction()

function(extend_cobot_tp_target target_name)
    cmake_parse_arguments(_arg
      ""
      "SOURCES_PREFIX;SOURCES_PREFIX_FROM_TARGET;FEATURE_INFO"
      "CONDITION;DEPENDS;PUBLIC_DEPENDS;DEFINES;PUBLIC_DEFINES;INCLUDES;PUBLIC_INCLUDES;SOURCES;EXPLICIT_MOC;SKIP_AUTOMOC;EXTRA_TRANSLATIONS;PROPERTIES"
      ${ARGN})
  if (${_arg_UNPARSED_ARGUMENTS})
    message(FATAL_ERROR "Error! Unparsed arguments in function <extend_cobot_tp_target>!")
  endif()

  condition_info(_extra_text _arg_CONDITION)
  if (NOT _arg_CONDITION)
    set(_arg_CONDITION ON)
  endif()
  if (${_arg_CONDITION})
    set(_feature_enabled ON)
  else()
    set(_feature_enabled OFF)
  endif()
  if (_arg_FEATURE_INFO)
    add_feature_info(${_arg_FEATURE_INFO} _feature_enabled "${_extra_text}")
  endif()
  if (NOT _feature_enabled)
    return()
  endif()

  if (_arg_SOURCES_PREFIX_FROM_TARGET)
    if (NOT TARGET ${_arg_SOURCES_PREFIX_FROM_TARGET})
      return()
    else()
      get_target_property(_arg_SOURCES_PREFIX ${_arg_SOURCES_PREFIX_FROM_TARGET} SOURCES_DIR)
    endif()
  endif()

  add_cobot_tp_depends(${target_name}
    PRIVATE ${_arg_DEPENDS}
    PUBLIC ${_arg_PUBLIC_DEPENDS})

  target_compile_definitions(${target_name}
    PRIVATE ${_arg_DEFINES}
    PUBLIC ${_arg_PUBLIC_DEFINES} )

  target_include_directories(${target_name} PRIVATE ${_arg_INCLUDES})

  add_public_includes(${target_name} "${_arg_PUBLIC_INCLUDES}")

  if (_arg_SOURCES_PREFIX)
    foreach(source IN LISTS _arg_SOURCES)
      list(APPEND prefixed_sources "${_arg_SOURCES_PREFIX}/${source}")
    endforeach()

    if (NOT IS_ABSOLUTE ${_arg_SOURCES_PREFIX})
      set(_arg_SOURCES_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/${_arg_SOURCES_PREFIX}")
    endif()
    target_include_directories(${target_name} PRIVATE $<BUILD_INTERFACE:${_arg_SOURCES_PREFIX}>)

    set(_arg_SOURCES ${prefixed_sources})
  endif()
  target_sources(${target_name} PRIVATE ${_arg_SOURCES})

  foreach(tempStr IN LISTS _arg_SOURCES)
  endforeach()

  add_public_headers(${target_name} "${_arg_SOURCES}")

  foreach(file IN LISTS _arg_EXPLICIT_MOC)
    set_explicit_moc(${target_name} "${file}")
  endforeach()

  foreach(file IN LISTS _arg_SKIP_AUTOMOC)
    set_property(SOURCE ${file} PROPERTY SKIP_AUTOMOC ON)
  endforeach()

  add_translation_files(${target_name} "${_arg_EXTRA_TRANSLATIONS}")

  if (_arg_PROPERTIES)
    set_target_properties(${target_name} PROPERTIES ${_arg_PROPERTIES})
  endif()
endfunction()

