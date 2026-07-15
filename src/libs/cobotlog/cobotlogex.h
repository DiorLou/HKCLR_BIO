#ifndef COBOTLOGEX_H
#define COBOTLOGEX_H

#include <QThread>
#include <QDateTime>
#include "cobotlog.h"

#define FREQ_LOG_PRINT_TIMESTAMP_THREAD FREQ_LOG_INFO(QString("*** FREQ LOG ***[%1][%2][%3][%4]") \
                      .arg(__FUNCTION__, QString::number(__LINE__), QString::number(QDateTime::currentMSecsSinceEpoch()), \
                           QString::number(reinterpret_cast<intptr_t>(QThread::currentThreadId()))));

#define FREQ_LOG_PRINT_TIMESTAMP   FREQ_LOG_INFO(QString("*** FREQ LOG ***[%1][%2][%3]") \
                      .arg( __FUNCTION__, QString::number(__LINE__), QString::number(QDateTime::currentMSecsSinceEpoch())));

#endif  // COBOTLOGEX_H
