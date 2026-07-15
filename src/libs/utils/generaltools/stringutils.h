#pragma once

#include "labeldata.h"
#include "generaltools_global.h"
#include <QString>
#include <QObject>

class GENERALTOOLS_EXPORT StringUtils : public QObject
{
    Q_OBJECT
public:
    static QString getUuid();

    static bool isDigital(QString str);
    static bool isContainChinese(const QString &str);

    static QString getElidedText(const QString &text, int showLen);

    static QString getEncriptCode(const QString &str);
    static bool isValidName(const QString &name, const QString &exp);

    static bool isKeyWord(const QStringList &sKeyWords,
                          const QString &str,
                          Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    static QString filterKeyWord(const QStringList &sKeyWords,
                                 const QString &str,
                                 Qt::CaseSensitivity cs = Qt::CaseSensitive);

    static bool ipStringIsValid(const QString &str, QString *errorStr = 0);

    static QString stringListToString(const QStringList &in, const QString splitSign = " ");

    static bool isNewVersion(const QString &version, const QString &newVersion);
};
