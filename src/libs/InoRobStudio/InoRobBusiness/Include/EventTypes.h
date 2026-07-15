#pragma once
/**
 * 事件类型宏定义
 **/
#define EVENT_WARM_UP_MACHINE          0x0001  // 自动热机实时信息改变事件
#define EVENT_LOADID_CALSTATEANDEND    0x0002  // 空载校准/负载辨识结果改变事件
#define EVENT_IND_AXIS_IN_USING        0x0003  // 独立轴状态改变事件
#define EVENT_LOADPOINTS_HAD_RUN       0x0004  // LoadPoints指令触发事件
#define EVENT_CMD_MESSAGEBOX           0x0005  // 指令弹框触发事件
#define EVENT_MASTERPAGE_CONNECT_STATE 0x0006  // 主控连接状态事件
#define EVENT_SLAVEPAGE_CONNECT_STATE  0x0007  // 从控连接状态事件
#define EVENT_REMOTE_DEVICE_STATE      0x0008  // 监控页面远端设备连接状态事件
#define EVENT_VISION_DATA_MASTER       0x0009  // 主控视觉监控数据事件
#define EVENT_VISION_DATA_SLAVE        0x000A  // 从控视觉监控数据事件
#define EVENT_INTERZONES_STATUS        0x000B  // 干涉区状态变更事件
#define EVENT_ZEROPOINT_DOWELCHECK     0x000C  // 零点校准定位销检查事件
#define EVENT_ECATSLAVEMANAGE_STATE    0x000D  // ECAT从站管理状态事件
#define EVENT_ZEROPOINT_SENSOR_STATE   0x000E  // 零点校准碰撞传感器状态事件
#define EVENT_EIPSLAVEMANAGE_STATE     0x0010  // EIP从站管理状态事件
#define EVENT_AUTHRITY_CHANGE          0x0012  // 控制权改变
#define EVENT_FILE_OPERATION           0X0014  // 文件读写指令
#define EVENT_STATIONSTATUS_CHANGE     0x0015  // 工位状态事件
#define EVENT_REDUCER_LIFE_CAL         0X0016  // 减速机寿命计算结果
#define EVENT_SCREW_LIFE_CAL           0X0017  // 丝杆寿命计算结果
#define EVENT_FORCE_CTRL_EXPORT_LOG    0x0026  // 力控接收日志导出路径并相应导出日志的请求
#define EVENT_COMPLETE_FRIC_IDENTIFY            0x0040  // 完成摩擦辨识计算事件
#define EVENT_COMPLETE_BACKLASH_IDENTIFY        0x0041  // 完成间隙辨识计算事件
