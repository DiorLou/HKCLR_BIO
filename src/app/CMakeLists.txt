if(Qt6_FOUND)
    set(QT_VERSION 6)
elseif(Qt5_FOUND)
    set(QT_VERSION 5)
endif()

if(MSVC AND QT_VERSION EQUAL 5)
    message("-DINOCOBOTTP_MSVC_QT5")
    add_definitions(-DINOCOBOTTP_MSVC_QT5)
endif()

update_plugin_dll("${__COBOT_PLUGINS}")

option(TPBox_Enabled OFF)


if(ANDROID)
  include(InoCobotTP_CMake/InoCobotTP_Android_armx64-v8a)
else()
  include(InoCobotTP_CMake/InoCobotTP_Windows_x64)
endif()


add_cobot_tp_executable(${COBOT_TP_APP_TARGET}
  DEPENDS
    ${Target_Depends_List}
  INCLUDES
    ${BreakPad_Include}
  DEFINES
    COBOT_TP_CASED_ID="1.0.0"
    COBOT_TP_COMPAT_VERSION="1.0.0"
    COBOT_TP_MAJOR_VERSION="1"
    COBOT_TP_MINOR_VERSION="0"
    COBOT_TP_PATCH_VERSION="0"
    RELATIVE_PLUGIN_PATH="${RELATIVE_PLUGIN_PATH}"
  SOURCES
    main.cpp
    application.cpp
    application.h
    ${orpePath}
    ${sharePath}
    ${BreakPad_ExtSrc}
  PROPERTIES
    WIN32_EXECUTABLE ON
)

# The app uses QApplication / QFontDatabase → requires Qt Widgets + Gui.
if(TARGET ${COBOT_TP_APP_TARGET})
  target_link_libraries(${COBOT_TP_APP_TARGET} PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Sql
    Metatype
  )

  # Trimmed teach-demo: most libs are linked as IMPORTED DLLs. When their source
  # `.cpp` files are removed from the repo, we must explicitly link the exe
  # against those IMPORTED targets (otherwise we get unresolved `__imp__`).
  set(_teach_demo_app_imports
    Dialog
    TeachController
    Authority
    Utils
    Instance
    Metatype
    GeneralTools
    MultiThreadTools
    CustomComponent
    DataBase
    Common
    Tcp
    PluginEngine
    VirtualKeyboard
    CobotLog
    FlowWidget
    Simulator
    OSUpdate
    Linker
    DataService
    Communication
    InoRobUdf
    InoRobUtil
    InoRobLog
    InoRobBusiness
  )

  target_link_libraries(${COBOT_TP_APP_TARGET} PRIVATE ${_teach_demo_app_imports})

  # Imported targets are link-time dependencies only; CMake does not copy their
  # runtime DLLs beside the executable automatically.  Keep the deploy folder
  # self-contained so packaged builds also run on machines without the source
  # tree (for example, libAuthority.dll is required during process startup).
  foreach(_runtime_target IN LISTS _teach_demo_app_imports)
    if(TARGET "${_runtime_target}")
      get_target_property(_is_imported "${_runtime_target}" IMPORTED)
      if(_is_imported)
        add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${_runtime_target}>"
            "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>"
          VERBATIM
        )
      endif()
    else()
      # Imported targets created in src/libs are directory-scoped and are not
      # visible here.  Deploy their known runtime DLL without making the target
      # GLOBAL, which would also propagate incompatible legacy include paths.
      set(_runtime_dll "")
      foreach(_runtime_root IN ITEMS
          "${PROJECT_SOURCE_DIR}/prebuilt_demo/windows-mingw-x64/bin"
          "${PROJECT_SOURCE_DIR}/prebuilt/windows-mingw-x64/bin")
        if(EXISTS "${_runtime_root}/lib${_runtime_target}.dll")
          set(_runtime_dll "${_runtime_root}/lib${_runtime_target}.dll")
          break()
        endif()
      endforeach()
      if(_runtime_dll)
        add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${_runtime_dll}"
            "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>"
          VERBATIM
        )
      endif()
    endif()
  endforeach()

  # Qt SQL drivers are plugins loaded at runtime, so linking Qt::Sql does not
  # copy them automatically.  Without qsqlite.dll QSQLITE is not listed in
  # QSqlDatabase::drivers() and application database initialization fails.
  set(_qt_sqlite_plugin "${Qt${QT_VERSION_MAJOR}_DIR}/../../../plugins/sqldrivers/qsqlite.dll")
  get_filename_component(_qt_sqlite_plugin "${_qt_sqlite_plugin}" ABSOLUTE)
  if(EXISTS "${_qt_sqlite_plugin}")
    add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>/sqldrivers"
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${_qt_sqlite_plugin}"
        "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>/sqldrivers/qsqlite.dll"
      VERBATIM
    )
  else()
    message(WARNING "Qt SQLite driver not found: ${_qt_sqlite_plugin}")
  endif()

  # Deploy the Qt runtime libraries and plugins required when launching the
  # executable outside Qt Creator.  Qt Creator injects its Qt bin directory
  # into PATH, which can otherwise hide missing deployment files.
  set(_qt_deploy_tool "${Qt${QT_VERSION_MAJOR}_DIR}/../../../bin/windeployqt.exe")
  get_filename_component(_qt_deploy_tool "${_qt_deploy_tool}" ABSOLUTE)
  if(EXISTS "${_qt_deploy_tool}")
    set(_qt_deploy_args --no-translations --no-compiler-runtime)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      list(APPEND _qt_deploy_args --debug)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
      list(APPEND _qt_deploy_args --release)
    endif()
    add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
      COMMAND "${_qt_deploy_tool}" ${_qt_deploy_args}
        "$<TARGET_FILE:${COBOT_TP_APP_TARGET}>"
      VERBATIM
    )
  else()
    message(WARNING "Qt deployment tool not found: ${_qt_deploy_tool}")
  endif()

  # windeployqt scans the executable and Qt plugins, but not every prebuilt
  # business DLL beside it.  Those DLLs use these Qt modules indirectly, so
  # deploy the complete module set requested by this project as well.
  get_filename_component(_qt_runtime_dir
    "${Qt${QT_VERSION_MAJOR}_DIR}/../../../bin" ABSOLUTE)
  foreach(_qt_runtime_module IN ITEMS
      Core Gui Widgets Network Sql Svg OpenGL OpenGLWidgets)
    set(_qt_runtime_dll
      "${_qt_runtime_dir}/Qt${QT_VERSION_MAJOR}${_qt_runtime_module}.dll")
    if(EXISTS "${_qt_runtime_dll}")
      add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${_qt_runtime_dll}"
          "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>"
        VERBATIM
      )
    endif()
  endforeach()

  target_compile_definitions(${COBOT_TP_APP_TARGET} PRIVATE
    COBOT_TP_ID="teachpendant"
    COBOT_TRANSLATION_PREFIX="cobottp"
  )


  if(TARGET TeachDemoPluginCompileIface)
    target_link_libraries(${COBOT_TP_APP_TARGET} PRIVATE TeachDemoPluginCompileIface)
  endif()

  if(MINGW)
    # Reduce memory pressure for huge AUTORCC TUs (qrc_orpe.cpp) under MinGW.
    target_compile_options(${COBOT_TP_APP_TARGET} PRIVATE -O0 -fno-tree-vectorize)
  endif()
endif()

if(MINGW)
    file(COPY ${PROJECT_SOURCE_DIR}/third_party/gl/libs/win64/glut.dll DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${PROJECT_SOURCE_DIR}/third_party/gl/libs/win64/glut32.dll DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${PROJECT_SOURCE_DIR}/third_party/log4cplus/libs/win64/liblog4cplusU.dll DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${PROJECT_SOURCE_DIR}/third_party/lua/libs/win64/lua51.dll DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${PROJECT_SOURCE_DIR}/third_party/libssh2/mingw64/lib/libzlib.dll DESTINATION ${COBOT_TP_LIBRARY_PATH})
    file(COPY ${PROJECT_SOURCE_DIR}/third_party/iconv/windows/win64/mingw/libiconv-2.dll DESTINATION ${COBOT_TP_LIBRARY_PATH})

    set(_osg_mingw_bin "${PROJECT_SOURCE_DIR}/third_party/osg/mingw/bin")
    if(EXISTS "${_osg_mingw_bin}" AND TARGET ${COBOT_TP_APP_TARGET})
      set(_exe_dir "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>")

      file(GLOB _osg_mingw_dlls "${_osg_mingw_bin}/libosg*.dll")
      list(APPEND _osg_mingw_dlls "${_osg_mingw_bin}/libOpenThreads.dll")
      foreach(_dll IN LISTS _osg_mingw_dlls)
        if(EXISTS "${_dll}")
          add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_dll}" "${_exe_dir}"
            VERBATIM
          )
        endif()
      endforeach()

      if(EXISTS "${_osg_mingw_bin}/osgPlugins-3.6.5")
        add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory "${_exe_dir}/osgPlugins-3.6.5"
          COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${_osg_mingw_bin}/osgPlugins-3.6.5" "${_exe_dir}/osgPlugins-3.6.5"
          VERBATIM
        )
      endif()
    endif()

    set(_irs_tp_mingw_bin "${PROJECT_SOURCE_DIR}/src/libs/InoRobStudio/third_party/lib/windows/x64_mingw")
    if(EXISTS "${_irs_tp_mingw_bin}" AND TARGET ${COBOT_TP_APP_TARGET})
      set(_exe_dir "$<TARGET_FILE_DIR:${COBOT_TP_APP_TARGET}>")
      file(GLOB _irs_tp_dlls "${_irs_tp_mingw_bin}/*.dll")
      foreach(_dll IN LISTS _irs_tp_dlls)
        add_custom_command(TARGET ${COBOT_TP_APP_TARGET} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_dll}" "${_exe_dir}"
          VERBATIM
        )
      endforeach()
    endif()
endif()
