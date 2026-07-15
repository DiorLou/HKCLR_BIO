#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "TechnologyGrpc.grpc.pb.h"
#include "VisionCalibrationDataType.h"
#include "FollowCraftDataType.h"
#include "../InoRobBusiness/Controller/IController.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace google::protobuf;
using namespace InoRobBusinessGrpc;

namespace InoRobBusiness
{
class TechnologyService final : public TechnologyGrpc::Service
{
#pragma region 数据转换

#pragma endregion

#pragma region 构造与析构

private:
    IController *_pController = nullptr;
    IConnection *_pConnection = nullptr;

public:
    TechnologyService(IController *pController);
    ~TechnologyService();

#pragma endregion

#pragma region 业务逻辑

public:
    // 视觉标定-配置视觉标定到控制器
    ::grpc::Status writeVisionCalibFile(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::writeVisionCalibFile_Request *request, ::google::protobuf::Int32Value *response) override;
    // 视觉标定-计算标定结果
    ::grpc::Status calCalibResult(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::calCalibResult_Request *request, ::InoRobBusinessGrpc::calCalibResult_Response *response) override;

    // 跟随工艺-写入跟随工艺配置文件到控制器
    ::grpc::Status writeFollowConfigFile(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::writeFollowConfigFile_Request *request, ::google::protobuf::Int32Value *response) override;

    // 跟随工艺-编码器分辨率计算
    ::grpc::Status calEncoderRatio(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::CalEncoderRatio_Request *request, ::InoRobBusinessGrpc::CalEncoderRatio_Response *response) override;

    // 跟随工艺-计算标定结果
    ::grpc::Status followCalibResult(::grpc::ServerContext *context, const ::InoRobBusinessGrpc::FollowCalibResult_Request *request, ::InoRobBusinessGrpc::FollowCalibResult_Response *response) override;

#pragma endregion

#pragma region 内部调用-视觉标定

private:
    /**
     * @brief 解析本地视觉标定数据json文件，解析到的数据存入到缓存中
     * @return 成功返回0，其他请见错误码
     */
    int analysisFile(const std::string &cfgFilePath, AllCalibConfigs &cfg);

    /**
     * @brief 反序列化所有标定参数配置
     * @param jsn json节点指针
     * @param data 所有标定参数配置
     * @return 成功true，失败false
     */
    bool deserializeAllCalibConfig(cJSON *jsn, AllCalibConfigs *data);

    /**
     * @brief 反序列化标定参数配置
     * @param jsn json节点指针
     * @param data 标定参数配置
     * @return 成功true，失败false
     */
    bool deserializeCalibConfig(cJSON *jsn, CalibConfig *data);

    /**
     * @brief 反序列化相机基础参数
     * @param jsn json节点指针
     * @param data 相机基础参数
     * @return 成功true，失败false
     */
    bool deserializeCameraInfo(cJSON *jsn, CameraInfo *data);

    /**
     * @brief 根据当前参数，让控制器计算标定结果(四轴)
     * @param matrix 输出，标定矩阵
     * @param result 输出，标定结果(误差)
     * @return 成功返回0，其它请见错误码
     */
    int writeCalibResultFourAxis(AllCalibConfigs &cfg, int visionIndex, double matrix[VC_CALIB_MATRIX_SIZE], CalibResult &result);

    /**
     * @brief 根据当前参数，让控制器计算标定结果(六轴)
     * @param matrix 输出，标定矩阵
     * @param result 输出，标定结果(误差)
     * @return 成功返回0，其它请见错误码
     */
    int writeCalibResultSixAxis(AllCalibConfigs &cfg, int visionIndex, double matrix[VC_CALIB_MATRIX_SIZE], CalibResult &result);

#pragma endregion

#pragma region 内部调用-跟随工艺

private:
    /**
     * @brief 绝对值函数模板
     * @tparam T 
     * @param value 
     * @return 
    */
    template <typename T>
    T AbsVar(T value)
    {
        return (value < 0) ? -value : value;
    }
    
    /**
     * @brief ftp传输跟随工艺配置文件给控制器
     * @param filePath 本地跟随工艺配置文件路径
     * @return 成功返回0，其它错误
    */
    int uploadFollowCfgFile(const std::string &filePath);

    /**
     * @brief 通知控制器更新跟随工艺配置
     * @param funcID 
     *  0 --- CapturePosCompensation + IsMonitor + IsEnable     补偿类参数                  (补偿量（6）、使能、监控)
     *  1 --- BasicPara                                         基本参数                    （传送带类型、编码器通道、关联用户坐标系Id、检测类型）
     *  2 --- EncoderPara                                       编码器参数                 （分辨率）
     *  3 --- ObjCaliPara                                       工件高度参数               (工件高度数组（16）)
     *  4 --- BoundaryPara                                      边界参数                  （边界类型，上下界（二选一）（普通（4）+倾斜（6）））
     *  5 --- CameraBasicPara                                   相机基本参数              （相机DO、拍照距离、触发沿、数据类型、重复检测判定距离）
     *  5 --- SensorPara                                        传感器参数                （传感器DI、触发沿、工件类型、重复剔除距离）
     *  6 ---                                                   视觉标定结果              （标定矩阵（16）、标定误差（8））
     *  7 --- VisionOTMPara                                     视觉一拖多参数             (开关状态、主从选择、成员数量、主控IP、成员索引）
     * @param index 更新配置的编号
     * @return 成功返回0，其它错误
    */
    int applyFollowConfig(uint32_t funcID, uint32_t index);

        /**
     * @brief 跟随工艺-获取偏移后的点集合
     * @param beltType 传送带类型: 0-直线型、1-圆盘型
     * @param encoderRatio 编码器分辨率
     * @param beltCntPose 偏移后的机器人点
     * @param beltPosForVision 相机取点时传送带的位置
     * @param wobjCoorId 关联工件坐标系的Id
     * @param robotPoints 偏移前的点集合
     * @param offsetPoints 偏移后的点集合
     * @return
     */
    int getFollowOffsetPoints(int32 beltType, double encoderRatio, int64 beltCntPose, int64 beltPosForVision, int32 wobjCoorId, const vector<CaliPoint> &robotPoints, vector<CaliPoint> &offsetPoints);

    /**
     * @brief 计算偏移后示教点
     * @param offsetPoint 输出
     * @return 0:成功
     */
    int readOffsetPointsFromController(CnvorOffsetPoint &offsetPoint);

    /**
     * @brief 从控制器获取标定计算结果：读取标定矩阵和误差失败
     * @param caliPoint 
     * @param caliResult 
     * @return 
    */
    int readCnvorCaliResultFromController(const CnvorCaliPoint &caliPoint, CnvorCaliResult &caliResult);

#pragma endregion

};

}  // namespace InoRobBusiness
