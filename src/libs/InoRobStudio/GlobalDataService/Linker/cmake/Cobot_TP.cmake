if(WIN32)
    set(Linker_Depend ws2_32 winmm user32 Iphlpapi Userenv Dbghelp)
endif()


fun_add_cobot_tp_library(Linker SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core
  DEFINES
    LINKER_EXPORT WIN32_LEAN_AND_MEAN INOROBOT
  INCLUDES
      ${InoRobStudio_Public_Include_List}
      ${BOOST_DIR}
  DEPENDS
      ${Linker_Depend}
      InoRobLog
      InoRobUtil
  SOURCES
      ${InoLinker_Public_Src}
)

