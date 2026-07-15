#pragma once

#include <QObject>
#include <string>
#include "dllspec.h"
#include "signal_slot.h"

namespace InoRobBusiness
{
/**
* @brief  数据订阅(采用NNG开源库实现发布订阅，本部分为上位机软件订阅控制器部分)
* @author xiongriwei
*/
    struct SubscriberCommon
    {
        std::string Topic;
        std::string Content;
    };

    class INOROBBUSINESS_CLASS ISubscriber : public QObject
    {
        Q_OBJECT

    public:
        virtual ~ISubscriber()
        {
        }
        /*!
         * \brief 初始化
         */
        virtual void init() = 0;
    signals:
        // 通用事件（如果不是专用事件，就是通用事件）
        void common_signal(SubscriberCommon);

        // event 类型
        void event_logic_tree_item(std::string);  // 逻辑树节点UUID反馈事件

        // event 类型
        void event_logic_tree_item_Move(std::string);  // 逻辑树节点UUID 运动指令反馈事件

        // sysevent 类型
        void sysevent_timer_value(std::string);   // 计时器值反馈事件

        // event 类型
        void event_tragteach_status(std::string); // 拖动示教状态变化事件

        // event 类型
        void event_tragteach_autorecordpos(std::string); // 拖动示教记点事件

        // event 类型
        void event_tool_io_description(std::string);

        // event 类型
        void event_pallet_change(std::string);

        // event 类型
        void event_nng_keepalive(std::string);
    };

}
