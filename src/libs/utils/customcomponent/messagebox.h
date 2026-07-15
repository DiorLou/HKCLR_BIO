#pragma once

#include <QMessageBox>
#include "customcomponent_global.h"
#undef MessageBox

const int DO_NOT_PROCESS_REPETIVE = -1;

class CUSTOMCOMPONENT_EXPORT MessageBox : public QMessageBox
{
    Q_OBJECT

public:
    static int information(
        const QString hint,
        const StandardButton buttonRole1 = Ok,
        const StandardButton buttonRole2 = NoButton,
        const bool isNeedPrintMsg = true,
        const QPoint &pos = QPoint(-1, -1));

    static int critical(
        const QString &hint,
        const StandardButton buttonRole1 = Ok,
        const StandardButton buttonRole2 = NoButton,
        const bool isNeedPrintMsg = true,
        const QPoint &pos = QPoint(-1, -1));

    static int warning(
        const QString &hint,
        const StandardButton buttonRole1 = Ok,
        const StandardButton buttonRole2 = NoButton,
        const bool isNeedPrintMsg = true,
        const QPoint &pos = QPoint(-1, -1));

    static int warning(
        const QString &hint,
        const QString &detailedText,
        const StandardButton buttonRole1 = Ok,
        const StandardButton buttonRole2 = NoButton,
        const bool isNeedPrintMsg = true,
        const QPoint &pos = QPoint(-1, -1));

    static int question(
        const QString &hint,
        const StandardButtons buttonRole1 = StandardButtons(Yes | No),
        const StandardButton buttonRole2 = NoButton,
        const bool isNeedPrintMsg = true,
        const QPoint &pos = QPoint(-1, -1));

    static bool _question(const QString &hint)
    {
        return question(hint) == QMessageBox::Yes;
    }

    static int forceQuestion(
        const QString &hint,
        const StandardButtons buttonRole1 = StandardButtons(Yes | No),
        const StandardButton buttonRole2 = NoButton,
        const bool isNeedPrintMsg = true,
        const QPoint &pos = QPoint(-1, -1));
};

