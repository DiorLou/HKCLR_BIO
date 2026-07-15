#pragma once

#include <string>
#include <vector>
#include <map>
#include "DataTypeDef.h"
#include "GlobalDataTypes.h"

using namespace InoRobUtil;

namespace InoRobBusiness
{

#define VC_COORD_COUNT                16   // 视觉标定坐标系数量
#define VC_CALIB_POINT_COUNT          9    // 标定点数量
#define VC_BASE_POINT_COUNT           3    // 基准点数量(不区分轴数)
#define VC_BASE_POINT_COUNT_FOUR_AXIS 2    // 四轴需要取的基准点数量
#define VC_BASE_POINT_COUNT_SIX_AXIS  3    // 六轴需要取的基准点数量
#define VC_CAMERA_POS_COUNT           2    // 相机坐标数据个数
#define VC_ROBOT_JPOS_COUNT           6    // 机器人关节坐标数据个数
#define VC_ROBOT_JPOS_MAX_COUNT       8    // 机器人关节坐标数据最大个数，用于解析json
#define VC_CALIB_MATRIX_SIZE          9    // 标定矩阵大小，3x3
#define VC_CALIB_RESULT_COUNT         9    // 标定结果(误差)数据格式
#define VC_CAMERA_NAME_LENGTH         20   // 相机名称最大长度
#define VC_RECEIVE_DATA_COUNT         3    // TCP接受到的字符串是由多少种类数据组成的
#define VC_CAMERA_INFO_COUNT          10   // 相机基础参数数据个数
#define VC_IO_ID_RANGE_MIN            0    // 触发相机拍照的io号最小值
#define VC_IO_ID_RANGE_MAX            255  // 触发相机拍照的io号最大值

// 标定方式
enum class CalibMethod
{
    // 手动
    MANUAL = 0,
    // 半自动
    SEMI_AUTO,
    // 自动
    AUTO,
};

// 相机安装方式
enum class CameraInstallMethod
{
    // 固定俯视式
    FIX_UP_TO_DOWN = 1,
    // 固定仰视式
    FIX_DOWN_TO_UP,
    // 移动式J2
    MOVE_J2,
    // 移动式J4
    MOVE_J4,
    // 移动式J5
    MOVE_J5,
    // 移动式J6
    MOVE_J6,
};

// 相机触发方式
enum class TriggerMethod
{
    // IO(上升沿\下降沿)
    IO = 0,
    // 以太网通信
    TCP,
};

// IO信号类型
enum class IOSignalType
{
    // 上升沿
    RISING_EDGE = 0,
    // 下降沿
    FALLING_EDGE,
};

// 相机连接状态
enum class CameraConnectState
{
    // 未连接
    UNCONNECTED = 0,
    // 已连接
    CONNECTED,
};

// 控制器接受相机发来的数据的状态
enum class CameraMsgReceivedState
{
    // 完成
    FINISHED = 0,
    // 未完成
    UNFINISHED,
};

// 向控制器下发的相机相关指令
enum class CameraCommunicationCmd : int
{
    // 通知控制器向相机发送数据
    SEND_DATA = 1,
    // 通知控制器接受相机发送的数据
    RECEIVE_DATA,
    // 通知控制器断开与相机的连接
    DISCONNECT,
    // 通知控制器连接相机
    CONNECT = 5,
};

/**
 * @brief 相机基础信息
 */
struct CameraInfo
{
    CameraInfo()
    {
        Initialize();
    }

    void Initialize()
    {
        name = "";
        ip = "127.0.0.1";
        port = 60000;
        triggerMethod = TriggerMethod::TCP;
        tcpTriggerFlag = "";
        ioId = 0;
        ioSignalType = IOSignalType::RISING_EDGE;
        tcpDataHeader = "";
        tcpDataSeparator = "";
        tcpDataEnd = "";
    }

    CameraInfo &operator=(const CameraInfo &other)
    {
        this->name = other.name;
        this->ip = other.ip;
        this->port = other.port;
        this->triggerMethod = other.triggerMethod;
        this->tcpTriggerFlag = other.tcpTriggerFlag;
        this->ioId = other.ioId;
        this->ioSignalType = other.ioSignalType;
        this->tcpDataHeader = other.tcpDataHeader;
        this->tcpDataSeparator = other.tcpDataSeparator;
        this->tcpDataEnd = other.tcpDataEnd;
        return (*this);
    }

    bool operator==(const CameraInfo &other) const
    {
        if (this->name != other.name)
        {
            return false;
        }

        if (this->ip != other.ip)
        {
            return false;
        }

        if (this->port != other.port)
        {
            return false;
        }

        if (this->triggerMethod != other.triggerMethod)
        {
            return false;
        }

        if (this->tcpTriggerFlag != other.tcpTriggerFlag)
        {
            return false;
        }

        if (this->ioId != other.ioId)
        {
            return false;
        }

        if (this->ioSignalType != other.ioSignalType)
        {
            return false;
        }

        if (this->tcpDataHeader != other.tcpDataHeader)
        {
            return false;
        }

        if (this->tcpDataSeparator != other.tcpDataSeparator)
        {
            return false;
        }

        if (this->tcpDataEnd != other.tcpDataEnd)
        {
            return false;
        }

        return true;
    }

    std::string name;              // 相机名称
    std::string ip;                // 相机ip
    int port;                      // 相机端口号
    TriggerMethod triggerMethod;   // 相机触发方式
    std::string tcpTriggerFlag;    // tcp触发拍照的字符串指令
    int ioId;                      // IO触发id
    IOSignalType ioSignalType;     // IO触发信号类型
    std::string tcpDataHeader;     // tcp数据 - 帧头
    std::string tcpDataSeparator;  // tcp数据 - 分隔符
    std::string tcpDataEnd;        // tcp数据 - 结束符
};

/**
 * @brief 标定参数配置
 */
struct CalibConfig
{
    CalibConfig()
    {
        Initialize();
    }

    void Initialize()
    {
        coordId = 0;
        cameraInfo.Initialize();
        cameraInstallMethod = CameraInstallMethod::FIX_UP_TO_DOWN;
        calibMethod = CalibMethod::MANUAL;
        wobjId = 0;
        baseJPointType = 0;

        for (size_t i = 0; i < VC_CALIB_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_CAMERA_POS_COUNT; k++)
            {
                this->visionPoints[i][k] = 0.0;
            }
        }

        for (size_t i = 0; i < VC_CALIB_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_ROBOT_JPOS_COUNT; k++)
            {
                this->robotJPoints[i][k] = 0.0;
            }
        }

        for (size_t i = 0; i < VC_BASE_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_ROBOT_JPOS_COUNT; k++)
            {
                this->baseJPoints[i][k] = 0.0;
            }
        }

        calibPointDistance = 0.0;
        calibCenterPoint.Initialize();
        memset(&calibMatrix[0], 0, VC_CALIB_MATRIX_SIZE * sizeof(double));
        memset(&calibResult[0], 0, VC_CALIB_RESULT_COUNT * sizeof(double));
        wobjData.InitZero();
    }

    CalibConfig &operator=(const CalibConfig &other)
    {
        this->coordId = other.coordId;
        this->cameraInfo = other.cameraInfo;
        this->cameraInstallMethod = other.cameraInstallMethod;
        this->calibMethod = other.calibMethod;
        this->wobjId = other.wobjId;
        this->baseJPointType = other.baseJPointType;

        for (size_t i = 0; i < VC_CALIB_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_CAMERA_POS_COUNT; k++)
            {
                this->visionPoints[i][k] = other.visionPoints[i][k];
            }
        }

        for (size_t i = 0; i < VC_CALIB_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_ROBOT_JPOS_COUNT; k++)
            {
                this->robotJPoints[i][k] = other.robotJPoints[i][k];
            }
        }

        for (size_t i = 0; i < VC_BASE_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_ROBOT_JPOS_COUNT; k++)
            {
                this->baseJPoints[i][k] = other.baseJPoints[i][k];
            }
        }

        this->calibPointDistance = other.calibPointDistance;
        this->calibCenterPoint = other.calibCenterPoint;
        memcpy(&calibMatrix[0], &other.calibMatrix[0], VC_CALIB_MATRIX_SIZE * sizeof(double));
        memcpy(&calibResult[0], &other.calibResult[0], VC_CALIB_RESULT_COUNT * sizeof(double));
        this->wobjData = other.wobjData;
        return (*this);
    }

    bool operator==(const CalibConfig &other) const
    {
        if (this->coordId != other.coordId)
        {
            return false;
        }

        if (!(this->cameraInfo == other.cameraInfo))
        {
            return false;
        }

        if (this->cameraInstallMethod != other.cameraInstallMethod)
        {
            return false;
        }

        if (this->calibMethod != other.calibMethod)
        {
            return false;
        }

        if (this->wobjId != other.wobjId)
        {
            return false;
        }

        if (this->baseJPointType != other.baseJPointType)
        {
            return false;
        }

        for (size_t i = 0; i < VC_CALIB_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_CAMERA_POS_COUNT; k++)
            {
                if (std::abs(this->visionPoints[i][k] - other.visionPoints[i][k]) > 0.000001)
                {
                    return false;
                }
            }
        }

        for (size_t i = 0; i < VC_CALIB_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_ROBOT_JPOS_COUNT; k++)
            {
                if (std::abs(this->robotJPoints[i][k] - other.robotJPoints[i][k]) > 0.000001)
                {
                    return false;
                }
            }
        }

        for (size_t i = 0; i < VC_BASE_POINT_COUNT; i++)
        {
            for (size_t k = 0; k < VC_ROBOT_JPOS_COUNT; k++)
            {
                if (std::abs(this->baseJPoints[i][k] - other.baseJPoints[i][k]) > 0.000001)
                {
                    return false;
                }
            }
        }

        if (std::abs(this->calibPointDistance - other.calibPointDistance) > 0.000001)
        {
            return false;
        }

        if (!(this->calibCenterPoint == other.calibCenterPoint))
        {
            return false;
        }

        for (size_t i = 0; i < VC_CALIB_MATRIX_SIZE; i++)
        {
            if (std::abs(this->calibMatrix[i] - other.calibMatrix[i]) > 0.000001)
            {
                return false;
            }
        }

        for (size_t i = 0; i < VC_CALIB_RESULT_COUNT; i++)
        {
            if (std::abs(this->calibResult[i] - other.calibResult[i]) > 0.000001)
            {
                return false;
            }
        }

        if (!(this->wobjData == other.wobjData))
        {
            return false;
        }

        return true;
    }

    int coordId;                                                     // 视觉标定坐标系号
    CameraInfo cameraInfo;                                           // 相机基础参数
    CameraInstallMethod cameraInstallMethod;                         // 相机安装方式
    CalibMethod calibMethod;                                         // 视觉标定方式
    int wobjId;                                                      // 基准点对应的工件号
    int baseJPointType;                                              // 基准关节点位类型，0-末端工具标定基准点，1-相机视野中心标定基准点
    double visionPoints[VC_CALIB_POINT_COUNT][VC_CAMERA_POS_COUNT];  // 九点标定 - 相机点位集合
    double robotJPoints[VC_CALIB_POINT_COUNT][VC_ROBOT_JPOS_COUNT];  // 九点标定 - 机器人关节点位集合
    double baseJPoints[VC_BASE_POINT_COUNT][VC_ROBOT_JPOS_COUNT];    // 基准关节点位集合
    double calibPointDistance;                                       // 九点标定点位阵列中点位的间距
    JPos calibCenterPoint;                                           // 九点标定中心点
    double calibMatrix[VC_CALIB_MATRIX_SIZE];                        // 标定矩阵
    double calibResult[VC_CALIB_RESULT_COUNT];                       // 标定结果
    WobjData wobjData;                                               // 工件号对应的工件参数
};

/**
 * @brief 所有的标定参数配置，共16组
 */
struct AllCalibConfigs
{
    AllCalibConfigs()
    {
        Initialize();
    }

    void Initialize()
    {
        version = "";
        robotName = "";
        for (size_t i = 0; i < VC_COORD_COUNT; i++)
        {
            configs[i].Initialize();
        }
    }

    AllCalibConfigs &operator=(const AllCalibConfigs &other)
    {
        this->version = other.version;
        this->robotName = other.robotName;
        for (size_t i = 0; i < VC_COORD_COUNT; i++)
        {
            this->configs[i] = other.configs[i];
        }
        return (*this);
    }

    bool operator==(const AllCalibConfigs &other) const
    {
        if (this->version != other.version)
        {
            return false;
        }

        if (this->robotName != other.robotName)
        {
            return false;
        }

        for (size_t i = 0; i < VC_COORD_COUNT; i++)
        {
            if (!(this->configs[i] == other.configs[i]))
            {
                return false;
            }
        }

        return true;
    }

    std::string version;                  // 软件系统版本
    std::string robotName;                // 机器人名称(型号)
    CalibConfig configs[VC_COORD_COUNT];  // 标定配置参数集合
};

/**
 * @brief 标定结果
 */
struct CalibResult
{
    CalibResult()
    {
        Initialize();
    }

    void Initialize()
    {
        averageErrorX = 0.0;
        averageErrorY = 0.0;
        maxErrorX = 0.0;
        maxErrorY = 0.0;
        pixelX = 0.0;
        pixelY = 0.0;
        offsetX = 0.0;
        offsetY = 0.0;
    }

    CalibResult &operator=(const CalibResult &other)
    {
        this->averageErrorX = other.averageErrorX;
        this->averageErrorY = other.averageErrorY;
        this->maxErrorX = other.maxErrorX;
        this->maxErrorY = other.maxErrorY;
        this->pixelX = other.pixelX;
        this->pixelY = other.pixelY;
        this->offsetX = other.offsetX;
        this->offsetY = other.offsetY;
        return (*this);
    }

    bool operator==(const CalibResult &other) const
    {
        if (std::abs(this->averageErrorX - other.averageErrorX) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->averageErrorY - other.averageErrorY) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->maxErrorX - other.maxErrorX) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->maxErrorY - other.maxErrorY) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->pixelX - other.pixelX) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->pixelY - other.pixelY) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->offsetX - other.offsetX) > 0.000001)
        {
            return false;
        }

        if (std::abs(this->offsetY - other.offsetY) > 0.000001)
        {
            return false;
        }

        return true;
    }

    double averageErrorX;  // x方向平均误差
    double averageErrorY;  // y方向平均误差
    double maxErrorX;      // x方向最大误差
    double maxErrorY;      // y方向最大误差
    double pixelX;         // x方向像素当量
    double pixelY;         // y方向像素当量
    double offsetX;        // 标定工具x方向偏移
    double offsetY;        // 标定工具y方向偏移
};

}  // namespace InoRobBusiness
