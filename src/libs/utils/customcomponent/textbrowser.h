#pragma once

#include <QTextBrowser>
#include "customcomponent_global.h"

class CUSTOMCOMPONENT_EXPORT TextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    TextBrowser(QWidget *parent) :
        QTextBrowser(parent)
    {
    }
    void setSrcollAreaMargins(int left, int top, int right, int bottom)
    {
        setViewportMargins(left, top, right, bottom);
    }
};


// class CUSTOMCOMPONENT_EXPORT TextBrowser : public QTextBrowser
// {
//     Q_OBJECT

// public:
//     explicit TextBrowser(QWidget *parent = 0);

// public slots:
//     void setPlainText(const QString &text);
//     void setText(const QString &text);

//     void append(const QString &text);

//     void clear();

// protected:
//     void changeEvent(QEvent *event);

// private:
//     QString m_preText;
// };
