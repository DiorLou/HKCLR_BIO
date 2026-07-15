/****************************************************************
 * File Descrip : 控制器告警信息
 * Author       : ldh
 ****************************************************************/
#pragma once
#include <string>
#include <QObject>
#include "dllspec.h"
#include "DataTypeDef.h"
#include "DataSrvGlobal.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS IWarnInfo : public QObject
{
    Q_OBJECT

public:
    // 告警信息结构体
    struct WarnData
    {
        WarnData()
        {
        }

        WarnData(std::string timeStr, std::string code, std::string contentStr)
        {
            time = timeStr;
            errcode = code;
            content = contentStr;
        }

        std::string errcode = "";        // 错误码
        std::string time = "";           // 时间
        std::string content = "unknow";  // 内容
    };

    virtual ~IWarnInfo()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;
    /*!
     * \brief 设置报警监控使能状态
     * \param isEnable 是否启用报警监控
     */
    virtual void setWarnMonitorEnable(bool isEnable) = 0;
    /*!
     * \brief 获取控制器报警信息
     * \param startIndex 按最近顺序从startIndex索引开始获取
     * \param count 告警信息条数 最大1000
     * \return 报警信息
     */
    virtual std::vector<WarnData> &getWarningList(int startIndex = 0, int count = 1000) = 0;

    /*!
     * \brief 清除控制器报警信息文件
     * \return 0-成功
     */
    virtual int clearWarnInfo() = 0;
Q_SIGNALS:
    /*!
     * \brief 新增报警日志通知
     * \param errorCode 报警错误码
     * \param time 时间
     * \param deacribe 报警内容
     */
    void sigAddWarning(QString time, QString errorCode, QString content);
};
}  // namespace InoRobBusiness
