#pragma once
#include "dllspec.h"
#include <QObject>
#include "IInoRobBusiness.h"
using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS WarnInfo_V1 : public QObject
{
    Q_OBJECT

#pragma region 数据（结构体与枚举）

public:
    struct WarnData_V1
    {
        WarnData_V1()
        {
        }

        WarnData_V1(std::string timeStr, std::string code, std::string contentStr)
        {
            time = timeStr;
            errcode = code;
            content = contentStr;
        }

        std::string errcode = "";        // 错误码
        std::string time = "";           // 时间
        std::string content = "unknow";  // 内容
    };

    static bool WarnData_ToProxy(const IWarnInfo::WarnData &warnData, WarnData_V1 &warnData_V1);
    static bool WarnData_FromProxy(const WarnData_V1 &warnData_V1, IWarnInfo::WarnData &warnData);

#pragma endregion

#pragma region 构造与析构

private:
    IWarnInfo *_warnInfo = nullptr;

public:
    WarnInfo_V1(IWarnInfo *warnInfo);
    ~WarnInfo_V1();

#pragma endregion

#pragma region 业务逻辑

private:
    void sigAddWarningHandler(QString time, QString errorCode, QString content);

public:
    /*!
     * \brief 设置报警监控使能状态
     * \param isEnable 是否启用报警监控
     */
    void setWarnMonitorEnable(bool isEnable);

    /*!
     * \brief 获取控制器报警信息
     * \param startIndex 按最近顺序从startIndex索引开始获取
     * \param count 告警信息条数 最大1000
     * \return 报警信息
     */
    void getWarningList(std::vector<WarnInfo_V1::WarnData_V1> &vec, int startIndex = 0, int count = 1000);

    /*!
     * \brief 清除控制器报警信息文件
     * \return 0-成功
     */
    int clearWarnInfo();

Q_SIGNALS:
    /*!
     * \brief 新增报警日志通知
     * \param errorCode 报警错误码
     * \param time 时间
     * \param deacribe 报警内容
     */
    void sigAddWarning(QString time, QString errorCode, QString content);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
