#pragma once
#include <string>
#include "IInoRobBusiness.h"
#include "ISelfLearningVibrationSuppression.h"

namespace InoRobBusiness
{
/*
    自学习振动抑制
    Create by lcm at 2024/04/09 创建。
*/
class INOROBBUSINESS_CLASS SelfLearningVibrationSuppression : public ISelfLearningVibrationSuppression
{
    Q_OBJECT

public:
    SelfLearningVibrationSuppression(IDataSrvBase *pDataSrv, IConnection *pConnection, IMonitor *pMonitor, IProject *pProject);
    virtual ~SelfLearningVibrationSuppression();

    /**
     * @brief 机型本体的类型
     */
    enum RobotBodyType : int
    {
        // 四轴正装
        SCARA_A = 0,

        // 四轴倒装
        SCARA_R = 2,

        // 六关节
        ARTICULATEDARM_A = 3,
    };

public:
    virtual std::string fileCtrlPath() override;
    virtual std::string fileCtrlTempPath() override;
    virtual int backupFile(const std::string &localFolder, const std::string &ctrlPath) override;
    virtual int uploadFile(const std::string &localPath, const std::string &ctrlPath) override;
    virtual int sendWriteDataToFileCmd(SlvsDataWriteFileState &state) override;
    virtual int sendUpdateDataCmd() override;
    virtual int readUpdateDataState(SlvsDataUpdateState &state) override;
    virtual int resetData() override;
    virtual int clearData() override;

    virtual bool checkStatus() override;
    virtual int analysisFile(const std::string &localPath) override;
    SlvsFileRobotNameCheckResult getRobotNameCheckResult() const override;
    virtual int changeFileRobotName(const std::string &localPath) override;

    virtual void setClearBtnVisible(bool visible) override;
    virtual bool getClearBtnVisible() override;

private:
    /**
     * @brief 获取文件头中对应项的值
     * @param content 输入，文本内容
     * @param key 输入，项的键值
     * @return 对应项的值
     */
    std::string getValue(const std::string &content, const std::string &key);
    /**
     * @brief 检查文件机型与控制器机型是否匹配
     * @param robotName 文件头信息中机型名称
     * @return 匹配结果
     */
    SlvsFileRobotNameCheckResult checkRobotName(const std::string &robotName);
    /**
     * @brief 从机型名称中解析出机型数据
     * @param robotBodyName 输入，机型名称
     * @param type 输出，机器人类型
     * @param loadValue 输出，最大负载
     * @param armLength 输出，臂长
     * @param zLength 输出，丝杆行程
     */
    void analysisRobotName(const std::string &robotBodyName, RobotBodyType &type, int &loadValue,
                           int &armLength, int &zLength);
    /**
     * @brief 从机型名称中解析出机器人类型
     * @param robotBodyName 输出，机器人类型
     * @return
     */
    RobotBodyType getRobotBodyType(const std::string &robotBodyName);
    /**
     * @brief 从截断的字符串中解析出最大负载数值
     * @param strLoad 输入，包含最大负载数值的截断字符串
     * @return 最大负载数值
     */
    int getLoadParam(const std::string &strLoad);
    /**
     * @brief 从截断的字符串中解析出臂长和丝杆行程
     * @param strArm 输入，包含机器本体数值的截断字符串
     * @param armLength 输出，臂长
     * @param zLength 输出，丝杆行程
     */
    void getArmParams(const std::string &strArm, int &armLength, int &zLength);
    /**
     * @brief 从文件中解析出自学习振动抑制二进制数据
     * @param localPath 输入，本地路径
     * @param startIndex 输入，文件内容中数据开始的位置
     * @param data 输出，自学习振动抑制二进制数据
     */
    bool getData(const std::string &localPath, long startIndex, std::vector<unsigned char> &data);
    /**
     * @brief 将自学习振动抑制二进制数据追加写入到文件中
     * @param localPath 输入，本地路径
     * @param data 输入，自学习振动抑制二进制数据
     * @return
     */
    bool writeData(const std::string &localPath, std::vector<unsigned char> &data);
    /**
     * @brief 生成备份时的文件名称，需要带当前工程名和时间
     */
    std::string genBackupFileName(const std::string &srcFileName);

private:
    IDataSrvBase *_pDataSrv = nullptr;    // 通讯
    IConnection *_pConnection = nullptr;  // 连接
    IMonitor *_pMonitor = nullptr;        // 监控
    IProject *_pProject = nullptr;        // 工程

    bool _clearBtnVisible;  // 编程调试页面操作集合中，清除数据按钮的可见性
    SlvsFileRobotNameCheckResult _robotNameCheckRt = SlvsFileRobotNameCheckResult::MISMATCH; // 机型名称匹配结果
};
}  // namespace InoRobBusiness
