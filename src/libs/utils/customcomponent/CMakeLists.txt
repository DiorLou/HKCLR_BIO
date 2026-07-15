set(CUSTOM_SOURCE
  abstractwidget.h abstractwidget.cpp
  antishakebutton.h
  multicolorprogress.h
  cc_switchbutton/switchbutton.h
  cc_switchbutton/switchbuttoninside.h
  comboBox/combobox.h
  comboBox/dropdownlist.h
  customcomponent_global.h
  filedialog.h
  pushbutton/threestatusbutton.h
  pushbutton/debouncebutton.h
  pushbutton/paircheckablebutton.h
  delegate/checkboxdelegate.h
  delegate/comboxdelegate.h
  delegate/radiobuttondelegate.h
  pushbutton/tipbutton.h
  resprogressbar.h
  roundprogressbar.h
  textbrowser.h
  # maskwidget/maskwidget.h
  messagebox.h
  cc_radiobutton/radiobutton.h
  cc_tableviewdelegatelineedit/tableviewdelegatelineedit.h
  cc_tableviewmodel/tableviewmodel.h
  cc_lineedit/lineedit.h
  cc_define/regexstrdefine.h
  cc_define/valuestructdefine.h
  clickablelabel.h
  searchbox/searchbox.h
  splashscreen.h
  tableview.h
  tabwidget.h
  textedit.h
  texteditnofocus.h

  waitfeedbackprogressbar.h
  loadingbar.h
  stepguidebutton.h
  toolbox/toolbox.h
  toolbox/toolboxbutton.h
  toolbox/toolboxprivate.h
  toolbox/toolboxstyle.h
  multicolorprogress.cpp
  antishakebutton.cpp
  cc_switchbutton/switchbutton.cpp
  cc_switchbutton/switchbuttoninside.cpp
  comboBox/combobox.cpp
  comboBox/dropdownlist.cpp
  filedialog.cpp
  # maskwidget/maskwidget.cpp
  messagebox.cpp
  pushbutton/threestatusbutton.cpp
  pushbutton/debouncebutton.cpp
  pushbutton/paircheckablebutton.cpp
  pushbutton/tipbutton.cpp
  resprogressbar.cpp
  roundprogressbar.cpp
  searchbox/searchbox.cpp
  splashscreen.cpp
  textbrowser.cpp
  tableview.cpp
  cc_tableviewdelegatelineedit/tableviewdelegatelineedit.cpp
  cc_tableviewmodel/tableviewmodel.cpp
  cc_lineedit/lineedit.cpp
  cc_radiobutton/radiobutton.cpp
  delegate/checkboxdelegate.cpp
  delegate/comboxdelegate.cpp
  delegate/radiobuttondelegate.cpp
  clickablelabel.cpp
  waitfeedbackprogressbar.cpp
  textedit.cpp
  textediteditnofocus.cpp
  loadingbar.cpp
  stepguidebutton.cpp
  toolbox/toolbox.cpp
  toolbox/toolboxbutton.cpp
  toolbox/toolboxprivate.cpp
  # maskwidget/maskwidget.ui
  resprogressbar.ui
  tableviewdetaildelegate.cpp tableviewdetaildelegate.h
  cclabel.h cclabel.cpp
  ccpushbutton.cpp ccpushbutton.h
  rotatingprogressdialog.h rotatingprogressdialog.cpp
  delegate/lineeditdelegate.h delegate/lineeditdelegate.cpp
  delegate/lineeditcomponent.h delegate/lineeditcomponent.cpp
  delegate/lineeditcomponent.ui

  recognizedialog.h recognizedialog.cpp
)

if(Platform_Cobot_TP_Msvc_Win)
  list(APPEND CUSTOM_SOURCE
        abstractwidget_impl.h
  )
endif()

fun_add_cobot_tp_library(CustomComponent SHARED
  PUBLIC_DEPENDS
  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Svg
  DEFINES
  CUSTOMCOMPONENT_LIBRARY
  DEPENDS
  GeneralTools
  Metatype
  Instance
  CobotLog
  SOURCES
      ${CUSTOM_SOURCE}

)

target_include_directories (CustomComponent PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/cc_switchbutton
  ${CMAKE_CURRENT_SOURCE_DIR}/cc_radiobutton
  ${CMAKE_CURRENT_SOURCE_DIR}/cc_tableviewmodel
  ${CMAKE_CURRENT_SOURCE_DIR}/cc_lineedit
  ${CMAKE_CURRENT_SOURCE_DIR}/cc_define
  ${CMAKE_CURRENT_SOURCE_DIR}/comboBox
  ${CMAKE_CURRENT_SOURCE_DIR}/maskwidget
  ${CMAKE_CURRENT_SOURCE_DIR}/pushbutton
  ${CMAKE_CURRENT_SOURCE_DIR}/cc_tableviewdelegatelineedit
  ${CMAKE_CURRENT_SOURCE_DIR}/toolbox
  ${CMAKE_CURRENT_SOURCE_DIR})
