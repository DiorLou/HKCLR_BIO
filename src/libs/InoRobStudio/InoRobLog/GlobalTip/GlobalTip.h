#pragma once

#include <QObject>
#include "dllspec.h"

namespace InoRobLog
{
class GlobalOperateTip;

/*!
 * \brief 全局提示类
 */
class INOROBLOG_CLASS GlobalTip : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Tip类型
     */
    enum TipType : char
    {
        MESSAGE_TIP = 0,    // 消息Tip
        SUCCESS_TIP,        // 成功Tip
        WARNING_TIP,        // 警告Tip
        ERROR_TIP,          // 错误Tip
        MESSAGE_CLOSE_TIP,  // 带关闭消息Tip
        SUCCESS_CLOSE_TIP,  // 带关闭成功Tip
        WARNING_CLOSE_TIP,  // 带关闭警告Tip
        ERROR_CLOSE_TIP     // 带关闭错误Tip
    };
    Q_ENUM(TipType)

    /*!
     * \brief 带操作Tip类型
     */
    enum OperateTipType : char
    {
        MESSAGE_OPERATE_TIP = 0,  // 带操作消息Tip
        SUCCESS_OPERATE_TIP,      // 带操作成功Tip
        WARNING_OPERATE_TIP,      // 带操作警告Tip
        ERROR_OPERATE_TIP         // 带操作错误Tip
    };
    Q_ENUM(OperateTipType)

    static GlobalTip *getInstance()
    {
        static GlobalTip instance;
        return &instance;
    }
    GlobalTip(const GlobalTip &) = delete;
    GlobalTip &operator=(const GlobalTip &) = delete;

    /*!
     * \brief 获取当前新建GlobalOperateTip对象id号
     * \return id号
     */
    int getOperatorTipCurrentId() const;

    /*!
     * \brief 添加一个GlobalOperateTip对象
     * \param tip GlobalOperateTip对象
     */
    void addOperateTip(GlobalOperateTip *tip);

    /*!
     * \brief 通过id号移除_operateTips容器中的GlobalOperateTip对象
     * \param id id号
     */
    void removeOperateTipById(int id);

    /*!
     * \brief 通过id号触发_operateTips容器中的GlobalOperateTip对象executeOperate信号
     * \param id id号
     */
    void executeOperateTip(int id);

Q_SIGNALS:
    /*!
     * \brief 弹出提示信号
     * \param type 提示类型
     * \param tipInfo 提示信息
     */
    void popupTipSignal(TipType type, std::string tipInfo);

    /*!
     * \brief 弹出带操作提示信号
     * \param type 提示类型
     * \param id GlobalOperateTip对象id
     * \param tipInfo   提示信息
     * \param operateInfo   操作信息
     */
    void popupOperateTipSignal(OperateTipType type, int id, std::string tipInfo, std::string operateInfo);

private:
    GlobalTip();
    ~GlobalTip();

    // 当前GlobalOperateTip id号
    int _operatorTipCurrentId = 0;
    std::vector<GlobalOperateTip *> _operateTips;
};

/*!
 * \brief 全局带操作提示类
 */
class INOROBLOG_CLASS GlobalOperateTip : public QObject
{
    Q_OBJECT
public:
    GlobalOperateTip(GlobalTip::OperateTipType type, std::string tipInfo, std::string operateInfo);
    ~GlobalOperateTip();
    int getId() const;

Q_SIGNALS:
    // 执行操作信号
    void executeOperateSignal();

private:
    // 对象id号(唯一).GlobalTip通过UI层返回的id号检索到对应GlobalOperateTip对象.
    int id = 0;
};

/*!
 * \brief 弹出消息提示
 * \param tipInfo 消息信息
 */
INOROBLOG_CLASS extern inline void popMessageTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::MESSAGE_TIP, tipInfo);
}

/*!
 * \brief 弹出成功提示
 * \param tipInfo 成功提示信息
 */
INOROBLOG_CLASS extern inline void popSuccessTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::SUCCESS_TIP, tipInfo);
}

/*!
 * \brief 弹出警告提示
 * \param tipInfo 警告提示信息
 */
INOROBLOG_CLASS extern inline void popWarningTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::WARNING_TIP, tipInfo);
}

/*!
 * \brief 弹出错误提示
 * \param tipInfo 错误提示信息
 */
INOROBLOG_CLASS extern inline void popErrorTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::ERROR_TIP, tipInfo);
}

/*!
 * \brief 弹出带关闭消息提示
 * \param tipInfo 消息信息
 */
INOROBLOG_CLASS extern inline void popMessageCloseTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::MESSAGE_CLOSE_TIP, tipInfo);
}

/*!
 * \brief 弹出带关闭错误提示
 * \param tipInfo 成功提示信息
 */
INOROBLOG_CLASS extern inline void popSuccessCloseTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::SUCCESS_CLOSE_TIP, tipInfo);
}

/*!
 * \brief 弹出带关闭错误提示
 * \param tipInfo 警告提示信息
 */
INOROBLOG_CLASS extern inline void popWarningCloseTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::WARNING_CLOSE_TIP, tipInfo);
}

/*!
 * \brief 弹出带关闭错误提示
 * \param tipInfo 错误提示信息
 */
INOROBLOG_CLASS extern inline void popErrorCloseTip(std::string tipInfo)
{
    emit GlobalTip::getInstance()->popupTipSignal(GlobalTip::ERROR_CLOSE_TIP, tipInfo);
}
}  // namespace InoRobLog
