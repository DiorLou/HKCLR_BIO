#pragma once
#include <QObject>
#include "dllspec.h"
#include "../../../InoRobLog/Log.h"
using namespace InoRobLog;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS Log_V1
{
#pragma region 业务逻辑

public:
    static void traceForPlugin(std::string &msg);
    static void traceForPlugin(QString msg);

    static void debugForPlugin(std::string &msg);
    static void debugForPlugin(QString msg);

    static void infoForPlugin(std::string &msg);
    static void infoForPlugin(QString msg);

    static void warnForPlugin(std::string &msg);
    static void warnForPlugin(QString msg);

    static void errorForPlugin(std::string &msg);
    static void errorForPlugin(QString msg);

    static void criticalForPlugin(std::string &msg);
    static void criticalForPlugin(QString msg);

#pragma endregion
};

}  // namespace InoRobBusinessProxy
