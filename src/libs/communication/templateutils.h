#pragma once

#include "communicationthread.h"
#include "communication.h"
#include <QVariant>
#include <functional>
using namespace std;

template <typename T, typename funClass>
void getListDatas(
    const QVariant customData, const QList<T> &oldData,
    bool (funClass::*fun)(QList<T> &),
    void (CommunicationEngine::*signal)(const QVariant, const QList<int>, const QList<T>),
    bool ignoreSizeDifferent = false)
{
    function<bool(QList<T> &)> funBind
        = bind(fun, Communication::instance(), placeholders::_1);

    function<void(const QVariant, const QList<int>, const QList<T>)> signalBind
        = bind(signal,
               CommunicationEngine::instance(),
               placeholders::_1,
               placeholders::_2,
               placeholders::_3);

    QList<T> newData;
    QList<T> different;
    QList<int> index;
    if (funBind(newData)
        && compareAndObtainDifferentDatas(oldData, newData, index, different, ignoreSizeDifferent)) {
        emit signalBind(customData, index, different);
    }
}

template <typename T>
bool compareAndObtainDifferentDatas(
    const QList<T> &oldData, const QList<T> &newData,
    QList<int> &differentIndex, QList<T> &differentValues, bool ignoreSizeDifferent = false)
{
    int resSize = differentIndex.size();
    int size1 = oldData.size();
    int size2 = newData.size();
    differentIndex.clear();
    differentValues.clear();
    if ((size1 != size2 && ignoreSizeDifferent) || size1 == 0) {
        differentValues = newData;
        for (int i = 0; i < size2; ++i) {
            differentIndex.push_back(i);
        }
        return true;
    }

    if (size1 != size2){
        return false;
    }

    for (int i = 0; i < size1; ++i) {
        if (!(oldData[i] == newData[i])) {
            differentIndex.push_back(i);
            differentValues.push_back(newData[i]);
        }
    }
    return resSize != differentIndex.size();
}

#ifdef INOCOBOTTP_MSVC_QT5
template <typename T>
bool compareAndObtainDifferentDatas(
    const QVector<T> &oldData, const QVector<T> &newData,
    QVector<int> &differentIndex, QVector<T> &differentValues, bool ignoreSizeDifferent = false)
{
    int resSize = differentIndex.size();
    int size1 = oldData.size();
    int size2 = newData.size();
    differentIndex.clear();
    differentValues.clear();
    if ((size1 != size2 && ignoreSizeDifferent) || size1 == 0) {
        differentValues = newData;
        for (int i = 0; i < size2; ++i) {
            differentIndex.push_back(i);
        }
        return true;
    }

    if (size1 != size2){
        return false;
    }

    for (int i = 0; i < size1; ++i) {
        if (!(oldData[i] == newData[i])) {
            differentIndex.push_back(i);
            differentValues.push_back(newData[i]);
        }
    }
    return resSize != differentIndex.size();
}
#endif

inline void combinErrorStr(QString &errorStr, const QString &newStr)
{
    if(errorStr.isEmpty())
        errorStr += newStr;
    else
        errorStr += "\r\n" + newStr;
}
