file(GLOB_RECURSE PINYIN_SOCRCE
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/pinyin/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/pinyin/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/*.qrc
)

fun_add_cobot_tp_library(VirtualKeyboard SHARED
  PUBLIC_DEPENDS
    Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui
  DEPENDS
    Utils
    Metatype
    Instance
    CustomComponent
    GeneralTools
    Communication
    CobotLog
  DEFINES
    VIRTUALKEYBOARD_LIBRARY
  SOURCES
    virtualkeyboard.h virtualkeyboard.cpp
    promptcompletiontablemodel.h promptcompletiontablemodel.cpp

    DigitalKeyboard/digitalkeyboard.cpp DigitalKeyboard/digitalkeyboard.h
    DigitalKeyboard/digitalkeyboard.ui

    FullKeyboard/fullkeyboard.cpp     FullKeyboard/fullkeyboard.h
    FullKeyboard/fullkeyboard.ui
    ${PINYIN_SOCRCE}

    # LogicalExpressionKeyboard/logicalexpressionkeyboard.cpp  LogicalExpressionKeyboard/logicalexpressionkeyboard.h
    # LogicalExpressionKeyboard/logicexpresspropertysource.cpp  LogicalExpressionKeyboard/logicexpresspropertysource.h
    # LogicalExpressionKeyboard/logicalexpressionkeyboard.ui

    LogicalExpressionKeyboard1/logicalexpressionkeyboard.cpp  LogicalExpressionKeyboard1/logicalexpressionkeyboard.h
    LogicalExpressionKeyboard1/logicexpresspropertysource.cpp  LogicalExpressionKeyboard1/logicexpresspropertysource.h
    LogicalExpressionKeyboard1/logicalexpressionparser.cpp   LogicalExpressionKeyboard1/logicalexpressionparser.h
    LogicalExpressionKeyboard1/logicalexpressiontypeinferrer.cpp   LogicalExpressionKeyboard1/logicalexpressiontypeinferrer.h
    LogicalExpressionKeyboard1/logicalexpressionkeyboard.ui

    virtualkeyboard_global.h
    virtualkeyboardresource.qrc
)

# target_include_directories (VirtualKeyboard PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}/DigitalKeyboard
#     ${CMAKE_CURRENT_SOURCE_DIR}/FullKeyboard
#     ${CMAKE_CURRENT_SOURCE_DIR}/LogicalExpressionKeyboard)

target_include_directories (VirtualKeyboard PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/DigitalKeyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/FullKeyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/PinYinKeyboard/pinyin
    ${CMAKE_CURRENT_SOURCE_DIR}/LogicalExpressionKeyboard1)
