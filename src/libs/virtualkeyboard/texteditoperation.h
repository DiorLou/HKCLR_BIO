#pragma once

#include <QLineEdit>
#include <QTextEdit>

class Tools
{
public:
    static void insterTextToCurrentCursor(QLineEdit *edit, const QString &text);
    static void deleteTextFromCurrentCursor(QLineEdit *edit, int deleteCount);
    static void setCursorPosition(QLineEdit *edit,int pos);
    static int cursorPosition(QLineEdit *edit);
    static void CursorMoveLeft(QLineEdit *edit,int count = 1);
    static void CursorMoveRight(QLineEdit *edit,int count = 1);
    static void setText(QLineEdit *edit,const QString &);
    static QString getText(QLineEdit *edit);
    static void setSelectAll(QLineEdit *edit);
    static void deleteSelectedText(QLineEdit *edit);
};

