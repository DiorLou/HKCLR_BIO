#pragma once
#include <QObject>
#include "DataSrvGlobal.h"
#include "dllspec.h"
#include "RemainLifeCalculate/IRemainLifeCalculate.h"

/*
    维护
    Create by MaoZhiWei at 2023/10/9 增加维护编辑相关
    Update by WuJian at 2024/7/8 增加维保相关功能
*/

namespace InoRobBusiness
{
#define MAINTENANCE_AXIS_NUM (6)

// 维保组件类型
enum class MaintenanceModule : int8s
{
    ENCODER_BATTERY_USETIME = 0,  // 编码器电池使用时间
    SCREW_GREASE_USETIME,         // 丝杆油脂使用时间
    SCREW_DEPLETION,              // 丝杆损耗百分比
    SYNC_BELT_USETIME,            // 同步带使用时间
    REDUCER_GREASE_USETIME,       // 减速机油脂使用时间
    BALANCE_CYLINDER_SPRINT,      // 平衡缸弹簧
};

#pragma pack(1)

// 平衡缸弹簧维保数据
typedef struct BalCylinderSpringData
{
    BalCylinderSpringData()
    {
        Initialize();
    }
    void Initialize()
    {
        d64SpringUseCount = 0;                    // 当前使用次数
        f32UsePercentage = 0;                     // 当前使用百分比
        memset(&cTime[0], 0, 18 * sizeof(char));  // 上次维保时间
        bStatus = 1;                              // 当前状态 0 - 超阈值，待维保；1 - 小于阈值，正常
    }
    double d64SpringUseCount;
    float f32UsePercentage;
    char cTime[18];
    bool bStatus;
} BalCylinderSpringData;

// 平衡缸弹簧阈值与属性
typedef struct BalCylinderSpringPara
{
    BalCylinderSpringPara()
    {
        Initialize();
    }
    void Initialize()
    {
        i16SwitchMode = 0;
        d64Threshold = 0;
        f32LimitStress = 0;
        f32SpringDiameter = 0;
        f32SpringWireDiameter = 0;
        f32MaxJoint2Angle = 0;
    }
    int16s i16SwitchMode;         // 功能是否开启（0-未开启；1-开启）
    double d64Threshold;          // 平衡缸寿命阈值
    float f32LimitStress;         // 疲劳极限应力
    float f32SpringDiameter;      // 弹簧中径
    float f32SpringWireDiameter;  // 弹簧线径
    float f32MaxJoint2Angle;      // J2轴极限位置角度
} BalCylinderSpringPara;

// 平衡缸弹簧维保设置
typedef struct BalCylinderSpringParaSet
{
    BalCylinderSpringParaSet()
    {
        Initialize();
    }
    void Initialize()
    {
        d64SpringCount = 0;
        stBalCylinderSpring.Initialize();
    }
    double d64SpringCount;  // 初始值设置
    BalCylinderSpringPara stBalCylinderSpring;
} BalCylinderSpringParaSet;

// 维保时间（通用）
typedef struct MaintenanceTime
{
    UINT16 u16Year;
    UINT8 u8Month;
    UINT8 u8Day;
    UINT8 u8Hour;
    UINT8 u8Minute;
    UINT8 u8Second;

    void Initialize()
    {
        u16Year = 0;
        u8Month = 0;
        u8Day = 0;
        u8Hour = 0;
        u8Minute = 0;
        u8Second = 0;
    }

    MaintenanceTime()
    {
        Initialize();
    }
} MaintenanceTime;

// 维保数据（通用）
typedef struct MaintenanceData
{
    MaintenanceModule Module;                        // 组件类型
    UINT16 AxisNum;                                  // 轴数量
    UINT8 AxisNumEnable[MAINTENANCE_AXIS_NUM];       // 启用的轴，如[1, 0, 1, 0, 1, 0]表示1、3、5轴
    INT32 Status[MAINTENANCE_AXIS_NUM];              // 维保状态（0待维保，1正常）
    double MaintenanceVal[MAINTENANCE_AXIS_NUM];     // 维保值
    double Threshold[MAINTENANCE_AXIS_NUM];          // 维保阈值
    MaintenanceTime LastTime[MAINTENANCE_AXIS_NUM];  // 最后维保时间

    void Initialize()
    {
        Module = MaintenanceModule::ENCODER_BATTERY_USETIME;
        AxisNum = 0;

        for (int i = 0; i < MAINTENANCE_AXIS_NUM; i++)
        {
            AxisNumEnable[i] = 0;
            Status[i] = 1;
            MaintenanceVal[i] = 0.0;
            Threshold[i] = 0.0;
            LastTime[i].Initialize();
        }
    }

    MaintenanceData()
    {
        Initialize();
    }
} MaintenanceData;

#pragma pack()

class INOROBBUSINESS_CLASS IMaintenance : public QObject
{
    Q_OBJECT

public:
    virtual ~IMaintenance()
    {
    }
    /*!
     * \brief 初始化
     */
    virtual void init() = 0;

#pragma region 寿命核算
    // 寿命核算
    virtual IRemainLifeCalculate *getRemainLifeCalculatem() = 0;
#pragma endregion

#pragma region 系统诊断

    /*!
     * \brief 检查控制器USB是否连接
     * \return 连接状态
     */
    virtual bool checkControllerUSB() = 0;

    /*!
     * \brief 获取诊断的保存状态
     * \param 返回的保存信息结构体
     * \return
     */
    virtual int ReadErrSaveSta(ErrsaveSta &sta) = 0;

    /*!
     * \brief 获取诊断报告的导出状态
     * \param 返回的状态信息结构体
     * \return
     */
    virtual int ReadErrExportSta(ErrexportSta &sta) = 0;

    /*!
     * \brief 启动诊断
     * \param sys    是否选中系统
     * \param logic  是否选中逻辑
     * \param track  是否选中轨迹
     * \return 是否诊断成功
     */
    virtual int startDiagnose(bool sys, bool logic, bool track) = 0;

    /*!
     * \brief 停止诊断
     * \param sys    是否选中系统
     * \param logic  是否选中逻辑
     * \param track  是否选中轨迹
     * \return
     */
    virtual int stopDiagnose(bool sys, bool logic, bool track) = 0;

    /*!
     * \brief 启动导出报告
     * \param sys    是否选中系统
     * \param logic  是否选中逻辑
     * \param track  是否选中轨迹
     * \param expType  导出类型
     * \param expDest  导出目录 0USB 1控制器指定目录 2预检查控制器状态
     * \return
     */
    virtual int startExportReport(bool sys, bool logic, bool track, int expType, int expDest = 0) = 0;

#pragma endregion

#pragma region 平衡缸弹簧维保

    // 获取平衡缸弹簧维保数据
    virtual bool getBalCylinderSpringData(BalCylinderSpringData &balCylinderSpringData) = 0;
    // 平衡缸弹簧维保
    virtual bool setBalCylinderSpring(const BalCylinderSpringParaSet &balCylinderSpringParaSet) = 0;

    // 读取平衡缸弹簧阈值与属性
    virtual bool getBalCylinderSpringPara(BalCylinderSpringPara &balCylinderSpringPara) = 0;
    // 设置平衡缸弹簧阈值与属性
    virtual bool setBalCylinderSpringPara(const BalCylinderSpringPara &balCylinderSpringPara) = 0;

#pragma endregion

#pragma region 其它组件维保

    // 获取指定组件的维保信息（返回网络通信返回值）
    virtual int getMaintenanceDataRaw(MaintenanceModule maintenanceModule, MaintenanceData &maintenanceData) = 0;
    // 获取指定组件的维保信息
    virtual bool getMaintenanceData(MaintenanceModule maintenanceModule, MaintenanceData &maintenanceData) = 0;
    // 设置维保时间
    virtual bool setMaintenanceTime(MaintenanceModule maintenanceModule, UINT8 axis, MaintenanceTime maintenanceTime) = 0;
    // 设置维保阈值
    virtual bool setMaintenanceThreshold(MaintenanceModule maintenanceModule, UINT8 axis, double threshold) = 0;
    // 清空所有维保数据
    virtual bool maintenanceDataClear() = 0;
    // 备份维保数据
    virtual bool maintenanceDataBackup(const string &filePath) = 0;
    // 还原维保数据
    virtual bool maintenanceDataRestore(const string &filePath) = 0;
    // 备份维保数据TP软件使用
    virtual bool maintenanceDataTPBackup() = 0;
    // 还原维保数据TP软件使用
    virtual bool maintenanceDataTPRestore() = 0;

#pragma endregion
};

}  // namespace InoRobBusiness
