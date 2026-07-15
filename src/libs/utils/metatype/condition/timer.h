#pragma once
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMetaType>
#include <QVariant>
#ifdef INOCOBOTTP_MSVC_QT5
    #include <QDebug>
#endif

typedef struct InoTimerInfo {
    int timerIndex;
    double timerValue;
    int times;

    InoTimerInfo()
    {
        timerIndex = -1;
        timerValue = 0.0;
        times = 0;
    }

    bool isValid() const
    {
        return (timerIndex == -1 || timerValue < 0);
    }

    InoTimerInfo &operator=(const InoTimerInfo &other)
    {
        if (this != &other) {
            timerIndex = other.timerIndex;
            timerValue = other.timerValue;
            times = other.times;
        }

        return *this;
    }

    // 根据下标获取对应数据
    QVariant getData(int index) const
    {
        switch (index) {
        case 0:
            return this->timerIndex;
        case 1:
            return this->timerValue;
        case 2:
            return this->times;
        default:
            break;
        }
        return QString();
    }
} InoTimerInfo;
Q_DECLARE_METATYPE(InoTimerInfo)

inline InoTimerInfo getTimerInfo(std::string &sText)
{
    InoTimerInfo info;
    if (sText.empty()) {
        return info;
    }

    QJsonParseError jErr;
    QJsonDocument jDoc = QJsonDocument::fromJson(
        QString::fromStdString(sText).toUtf8(), &jErr);
    if (jErr.error != QJsonParseError::NoError){
        qDebug() << QString(jErr.errorString().toUtf8().constData());
    }

    if (jDoc.isObject()) {
        QJsonObject jObj = jDoc.object();
        if (!jObj.contains("TimerIndex") || !jObj.contains("Value")) {
            return info;
        }

        info.timerIndex = jObj.value("TimerIndex").toInt();
        info.timerValue = jObj.value("Value").toDouble();

        qDebug() << info.timerIndex << info.timerValue;
    }

    return info;
}
