#pragma once
#include "IMechUnitManage.h"
#include "IDataSrvBase.h"
#include "IInoRobBusiness.h"

#ifdef __linux__
    #define MASTER_SLAVE_CFG_PATH STATIC_CFG_PATH + std::string("MasterSlaveConfig/")
#else
    #define MASTER_SLAVE_CFG_PATH std::string("./static_config/MasterSlaveConfig/")
#endif

// 660N含有200B, 用于九州柜型本体轴
#define SLAVE_FILE_SV660N_1AXIS_ROBOT MASTER_SLAVE_CFG_PATH + "sv660n_1axis_init_Robot.txt"

// 660N无200B
#define MASTER_FILE                  MASTER_SLAVE_CFG_PATH + "master_init.txt"
#define SLAVE_FILE_SV660N_1AXIS      MASTER_SLAVE_CFG_PATH + "sv660n_1axis_init.txt"
#define SLAVE_FILE_SV660N_2AXIS      MASTER_SLAVE_CFG_PATH + "sv660n_2axis_init.txt"
#define SLAVE_FILE_IS620N_1AXIS      MASTER_SLAVE_CFG_PATH + "is620n_1axis_init.txt"
#define SLAVE_FILE_SV680N_1AXIS      MASTER_SLAVE_CFG_PATH + "sv680n_1axis_init.txt"
#define SLAVE_FILE_SV680L_1AXIS      MASTER_SLAVE_CFG_PATH + "sv680l_1axis_init.txt"
#define SLAVE_FILE_SV660N_STOP_1AXIS MASTER_SLAVE_CFG_PATH + "sv660n_1axis_spot_init.txt"
#define END_FILE                     MASTER_SLAVE_CFG_PATH + "end.txt"
#define CONFIG_FILE_DIR              MASTER_SLAVE_CFG_PATH
#define CONFIG_FILE_FOUR_AXIS        std::string("master-scara.xml")
#define CONFIG_FILE_FOUR_AXIS_TMP    std::string("master-scara.xml.tmp")
#define CONFIG_FILE_FOUR_AXIS_BK     std::string("master-scara.xml.bk")
#define CONFIG_FILE_SIX_AXIS         std::string("master-six.xml")
#define CONFIG_FILE_SIX_AXIS_TMP     std::string("master-six.xml.tmp")
#define CONFIG_FILE_SIX_AXIS_BK      std::string("master-six.xml.bk")
// 以下用于适配九州立柜的机型用，需要改个名称，因为系统软件setup中默认的xml配置文件名为：master-six-6.xml
#define CONFIG_FILE_SIX_SINGLE_AXIS     std::string("master-six-6.xml")
#define CONFIG_FILE_SIX_SINGLE_AXIS_TMP std::string("master-six-6.xml.tmp")
#define CONFIG_FILE_SIX_SINGLE_AXIS_BK  std::string("master-six-6.xml.bk")

// 机械单元种类数量
#define MECH_UNIT_TYPE_NUM 13
// 机械单元需校准数量
#define MECH_UNIT_CALIB_NUM 7

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS MechUnitManageDefault : public IMechUnitManage
{
    Q_OBJECT

#pragma region 构造与析构

private:
    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService;
    // 连接
    IConnection *_pConnection;
    // 监控
    IMonitor *_pMonitor;
    // 位置
    IPosition *_pPosition;
    // 运动
    IMotion *_pMotion;
    // 标定
    ICalibrate *_pCalibrate;
    // 用户
    IUser *_pUser;
    // 机械臂
    IRobotArm *_pRobotArm;
    // 调试
    IDebuger *_pDebuger;

public:
    MechUnitManageDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);
    ~MechUnitManageDefault();
    void init() override;
#pragma endregion 属性

    // 获取机械单元数量
    int GetMechUnitCount()override ;
    // 获取机械单元列表
    vector<MechUnitData> GetMechUnitList() override;

#pragma endregion

#pragma region 方法

    void InitData();

    // 添加机械单元
    bool AddMechUnit(int type, const char *name) override;

    // 添加机械单元前的数量检查
    int checkMechUnitNumBeforeAddMechUnit() override;

    // 删除机械单元
    bool RemoveMechUnit(const char *name) override;

    // 获取数据
    void GetData(MechUnitsCfgData *cfgData, MechUnitsCalibData *calibData);

    // 设置数据
    void SetData(MechUnitsCfgData *cfgData, MechUnitsCalibData *calibData);

    // 取当前工具号
    int GetCurTool();

    // 取机器人当前点
    bool GetCurRobPos(MechUnitCalibMethod calibMethod, RobPos &pos);

    // 外部轴取当前点做为零点值
    bool RecordAbsZero(string mechUnitName, int logicAxisIndex, int &value);

    // 运动到点
    bool MoveToPoint(MechUnitCalibMethod calibMethod, MoveType moveType, RobPos mPos, double lH, double mH, double rH);

    // 停止运动到点
    bool StopToPoint();

    //(PC)检查使用权限(管理员以上、控制权：PC)
    bool PCCheckAuthority();

    //(TP)检查使用权限(管理员以上、控制权：TP)
    bool TPCheckAuthority();

    // 检查保存许可（需要急停、示教模式下）
    bool CheckSavePermission();

    // 检查数据是否有修改
    bool CheckMechUnitDataModified(string mechUnitName);

    // 检查更新机械单元名称许可
    bool checkModifyMechUnitNamePerm(const std::string &newMechName);

    // 创建机械单元默认名称
    string CreateDefaultNameByMechUnitType(MechUnitType mechUnitType);

    // 计算标定结果(传入数组指针和数据数量，标定类型)
    bool CalculateCalibResult(RobPos calibPoints[MECHUNIT_CALIB_MID_POS_MAX_COUNT], MechUnitCalibMethod calibMethod, string unitName, Pose previousAxisPos, int axisNum, Pose &pos);

    // 计算XYZ和XZ导轨标定结果(传入数组指针和数据数量，标定类型)
    bool CalculateTrackCalibResult(RobPos calibPoints[MECHUNIT_CALIB_MID_POS_MAX_COUNT], MechUnitCalibMethod calibMethod, string unitName, int axisNum, Pose *pos, int16u mechUnitType);

    // 从控制器中获取机械单元配置文件并读取
    int ReadMechUnitCfgAndCalibDataFromFile();

    // 将机械单元数据写入到文件并下发到控制器
    bool WriteMechUnitCfgAndCalibDataToFile();

    // 发送非实时命令让控制器解析
    bool WriteMechUnitsCfg();

    // 读机械单元配置控制器是否配置成功信息
    int readMechUnitsCfg();

    // 修改机械单元名称
    void modifyMechName(const std::string &currMechName, const std::string &newMechName);

    // 根据机械单元下标号及选中的轴号更新轴属性数据
    vector<BUS_EXT_AXIS_PARAM_LIST> updateAxisDefaultDataByMechType(const int guideIndex, const int curSelectAxisIndex);

    // 获取机器人独立轴数据
    vector<BUS_EXT_AXIS_PARAM_LIST> getRobotIndAxisData();

    // 获取机械单元各轴的独立轴信息
    vector<BUS_IND_AXIS_PARAM_LIST> getAllMechUnitIsSupportIndAxisData();

    // 设置机器人独立轴属性
    void setRobotIndAxisAttribute(const int indAxisEnum, string &value);

    // 根据机械单元获取未使用的轴逻辑
    vector<int> readUnusedAxisLogicByMechUnit(const MechUnit &mechUnit, const int axisIndex);

    // 更新机械单元的轴映射和外部轴ID
    void updateMechUnitAxisMapAndAxisID(int8u curAxisLogic[EXT_AXIS_NUM], int guideIndex);

    // 检查机械转换表格中的XYZABC数据是否合理，超出则返回边界值
    double checkMechTransValueIsValid(const int column, const double value);

    // 检查轴属性表双击处是否需要修改
    int checkAxisAttributeIsNeedChanged(const int row);

    // 设置轴属性表中要修改的值，不符合要求自动设置一个合理值，并返回
    void setAxisAttributeValue(const int row, string &value, const int guideIndex, const int curSelectAxisIndex);

    // 取当前值为零点值
    int setCurrValueAsHomePoint(const int guideIndex, const int currAxisIndex);

    // 外部轴组态文件配置
    int externalAxisForceConfig();

    // 检查机械单元名称是否包含关键字
    int checkMechUnitNameIsKeyWord();

    // 检查保存时版本是否符合要求
    int checkVersionInfoWhenSaveMechUnit();

    // 检查配置的机械单元中是否包含新的导轨
    bool isContainNewTrackMechUnit();

    // 标定权限检查
    bool checkPermissionInCalib();

    // 保存机械单元配置文件及标定文件至系统前的权限检查
    bool checkPermissionBeforeSaveToSystem();

    // 机械单元操作权限检查
    bool checkMechUnitOperatePermission();

    // 强制组态权限检查
    bool checkExtAxisConfigPermission();

    // 保存机械单元文件至系统中
    int saveMechUnitFileToSystem();

    /*********************************数据查询接口*********************************/

    // 机械单元名称查询
    string MechUnitTypeNameSearch(MechUnitType type);

    // 机械单元类型查询
    MechUnitType mechUnitTypeSearch(const char *name);

    // 机械单元名称列表查询
    vector<string> mechUnitNameListSearch();

    // 机械单元轴数查询
    int MechUnitTypeAxisCountSearch(MechUnitType type);

    // 机械单元默认名称查询
    string MechUnitDefaultNameSearch(MechUnitType type);

    // 外部轴的编号对应的逻辑轴字符串查询
    string ExternalAxisNumNameSearch(ExternalAxisNum axisNum);

    // 转换关系名称查询
    string RelativeObjNameSearch(MechUnitType type, RelativeObject obj);

    // 外部轴类型名称查询
    string ExternalAxisTypeNameSearch(ExternalAxisType type);

    // 外部轴运动类型名称查询(旋转-旋转、旋转-直线)
    string ExternalAxisMoveTypeNameSearch(ExternalAxisMoveType type);

    // 外部轴设备类型名称查询
    string ExternalAxisDeviceTypeNameSearch(ExternalAxisDeviceType type);

    // 独立轴标志查询
    string IndependantAxisSupportFlagSearch(IndependantAxisSupportFlag type);

    // 外部轴伺服控制类型名称查询
    string ExternalAxisServoControlTypeNameSearch(ExternalAxisServoControlType type);

    // 运动类型名称查询
    string ExecuteMoveTypeNameSearch(MoveType type);

    // 标定点数查询
    int CalibPointCountSearch(MechUnitCalibMethod method);

    // 标定方法名称查询
    string CalibMethodNameSearch(MechUnitCalibMethod method);

    // 根据标定方法名称查询对应的类型MechUnitCalibMethod
    MechUnitCalibMethod calibMethodTypeSearchBasedName(const std::string &calibMethodName);

    // 机械单元对应的标定方法集合查询
    vector<string> MechUnitCalibMethodSearch(MechUnitType type);

    // 标定方法对应示教点名称数组
    vector<string> CalibMethodTeachPointNameSearch(MechUnitCalibMethod method);

    // 独立轴电机轴转向名称查询
    string IndAxisMotorRotationSearch(IndAxisMotorRotationType type);

    int readIndAxisInUsing(unsigned char *status, int size);

    int writeIndAxisReset(IndAxisStatus buf);

    // 通过大文件的方式将机械单元配置数据写入控制器
    bool writeMechUnitCfgToController();
#pragma endregion

private:
    // 添加机械单元许可
    bool AddMechUnitPremision(int type, const char *name);

    // 删除机械单元许可
    bool RemoveMechUnitPremision(const char *name);

    // 获取没有使用的轴编号
    vector<int> getUnusedAxisLogicNum(bool isContainCurUnit, const char *mechUnitName);

    // 获取当前选中的轴属性数据
    ExtAxisParamItem getSelectAxisAttribute(int guideIndex, int curSelectAxisIndex);

    // 获取当前选中轴的独立轴属性数据
    IndAxisParamItem getSelectIndAxisAttribute(int guideIndex, int curSelectAxisIndex);

    // 更新当前选中轴的属性
    void updateSelectedAxisAttribute(ExtAxisParamItem extParamItem);

    // 更新当前独立轴属性
    void updateSelectedIndAxisAttribute(ExtAxisParamItem extParamItem, IndAxisParamItem indParamItem);

    // 保存独立轴的相关属性
    void saveIndependentAxisData();

    // 获取轴属性对应的范围
    vector<std::string> getAxisAttributeRange(int axisAttrType);

    // 根据机械单元类型更新轴属性中参数名和范围
    vector<BUS_EXT_AXIS_PARAM_LIST> updateParamNameAndRange(MechUnitType mechType, int16s svType, int16s moveType);

    // 初始化可变的轴属性参数范围地图
    void initVariableAxisAttributeMap();

    int PutMechUnitCfgIoFile();

    int GetMechUnitCfgIoFile();

    int PutMechUnitCalibIoFile();

    int GetMechUnitCalibIoFile();

    bool PutCfgIoToFile();

    bool GetCfgIoFromFile();

    bool PutCalibIoToFile();

    bool GetCalibIoFromFile();

    bool CheckRestartAndModified();

    bool CheckDataConflict();

    // 连接状态变化(槽函数)
    void OnConnectionStatusChange(ControllerConnectionStatus status);

    ///******************主从站xml文件拼接相关******************///
    int GetElectrixBoxType(int16u &type);

    // 写入数据到本地文件
    bool PutXmlConfigDataToFile();

    // 本地文件下载到控制器
    int PutXmlDataFile();
    ///*******************************************************///

    // 获取机械单元配置权
    bool mechUnitAuthorityChanged(int8u &authority);

    // 检查平台是否有权限修改机械单元参数
    bool checkPlatformModifAuthority(string mechUnitName, bool tooltip = true);

    // 读取点焊代码屏蔽标志位；
    // true-屏蔽,使用FTP的方式下发；false-不屏蔽,使用大文件方式下发
    bool readSpotGunFlag();

private:
    // 机械单元数据
    MechUnitsCfgData *_mechUnitsCfgData;

    // 机械单元标定数据
    MechUnitsCalibData *_mechUnitsCalibData;

    // 机械单元控制器文件中数据
    MechUnitsCfgData *_mechUnitsCfgDataFromFile;

    // 机械单元控制器文件中标定数据
    MechUnitsCalibData *_mechUnitsCalibDataFromFile;

    // 机械单元列表
    vector<MechUnitData> _mechUnitList;

    // 可变的轴属性范围地图
    map<ExternalAxisDeviceType, vector<VariableAxisAttribute>> _variableAxisAttributeMap;

    // 机械单元类型轴数数组
    static const MechUnitTypeAxisCountStruct _mechUnitTypeAxisCountArray[MECH_UNIT_TYPE_NUM];

    // 机械单元类型名称数组
    static const vector<MechUnitTypeNameStruct> _mechUnitTypeNameArray();
    // static const MechUnitTypeNameStruct _mechUnitTypeNameArray[MECH_UNIT_TYPE_NUM];

    // 机械单元默认名称数组
    static const MechUnitTypeNameStruct _mechUnitDefaultNameArray[MECH_UNIT_TYPE_NUM];

    // 外部轴编号对应名称数组
    static const vector<ExternalAxisNumStruct> _externalAxisNumNameArray();

    // 机器人转换关系数组
    static const RelativeObjStruct _robotRelativeObjNameArray[1];

    // 导轨转换关系数组
    static const RelativeObjStruct _trackRelativeObjNameArray[2];

    // 导轨XYZ转换关系数组
    static const vector<RelativeObjStruct> _trackXYZRelativeObjNameArray();

    // 导轨XZ转换关系数组
    static const vector<RelativeObjStruct> _trackXZRelativeObjNameArray();

    // 导轨YZ转换关系数组
    static const vector<RelativeObjStruct> _trackYZRelativeObjNameArray();

    // 设备转换关系数组
    static const vector<RelativeObjStruct> _deviceRelativeObjNameArray();

    // 外部轴类型名称数组
    static const vector<ExternalAxisTypeStruct> _externalAxisTypeNameArray();

    // 外部轴运动类型名称数组
    static const vector<ExternalAxisMoveTypeStruct> _externalAxisMoveTypeNameArray();

    // 外部轴设备类型名称数组
    static const vector<ExternalAxisDrviceTypeStruct> _externalAxisDeviceTypeNameArray();

    // 独立轴支持标志
    static const vector<IndependantAxisSupportFlagStruct> _independantAxisSupportFlagArray();

    // 外部轴伺服控制类型名称数组
    static const vector<ExternalAxisServoControlTypeStruct> _externalAxisServoControlTypeNameArray();

    // 运动类型名称数组
    static const ExecuteMoveTypeStruct _executeMoveTypeNameArray[3];

    // 标定点数量数组
    static const CalibPointCountStruct _calibPointCountArray[6];

    // 标定方法名称数组
    static const vector<CalibMethodNameStruct> _calibMethodNameArray();

    // 机械单元对应标定方法数组
    static const vector<MechUnitCalibMethodStruct> _mechUnitCalibMethodArray();

    // 标定方法对应示教点名称数组
    static const vector<MechUnitCalibMethodTeachPointStruct> _mechUnitCalibMethodTeachPointArray();

    // 独立轴电机轴转向
    static const vector<IndAxisMotorRotationTypeStruct> _indAxisMotorRotationArray();

    // 逻辑轴编号
    static const ExternalAxisNum _axisLogicEnum[7];

    // 目前允许的最大机械单元数量(除机器人)
    static const int _maxMechUnitCount;

    // 本地机械单元配置文件路径
    static const std::string _localCfgPath;

    // 控制器配置文件路径
    static const std::string _remoteCfgPath;

    // 控制器标定文件路径
    static const std::string _remoteCalibPath;

    // 配置文件名称
    static const std::string _cfgFileName;

    // 配置文件临时名称
    static const std::string _tmpCfgFileName;

    // 配置文件备份名称
    static const std::string _bkCfgFileName;

    // 标定文件名称
    static const std::string _calibFileName;

    // 标定文件临时名称
    static const std::string _tmpCalibFileName;

    // 标定文件备份名称
    static const std::string _bkCalibFileName;

    // 控制器版本号后缀
    static const int _virsion_25;

    // 机械单元禁改数组
    vector<string> _vMechUnitProhModify;

    // 0：断电重启生效；1：立即生效
    int32u _recordControllerFlag;

    // 0：未修改；1：有修改
    int8u _modifiedMechUnits[EXT_AXIS_NUM + 1];
};

}  // namespace InoRobBusiness
