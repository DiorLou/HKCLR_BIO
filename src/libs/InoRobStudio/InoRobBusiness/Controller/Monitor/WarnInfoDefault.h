/****************************************************************
 * File Descrip : 控制器告警信息
 * Author       : ldh
 ****************************************************************/
#pragma once
#include "IDataSrvBase.h"
#include "IInoRobBusiness.h"
#include <unordered_set>

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS WarnInfoDefault : public IWarnInfo, public IRCSchedulerUser
{
    Q_OBJECT

public:
    WarnInfoDefault(string name, IDataSrvBase *dataService, QObject *parent = nullptr);

    virtual ~WarnInfoDefault();
    void init() override;
    void setWarnMonitorEnable(bool isEnable) override;

    std::vector<WarnData> &getWarningList(int startIndex = 0, int count = 1000) override;

    void execute() override;

    int clearWarnInfo() override;

private:
    void onConnectionStatusChanged(InoRobBusiness::ControllerConnectionStatus status);
    void onWarningIdChanged(int32s warningId);
    void onErrorIdChanged(int32s errorId);
    /*!
     * \brief 加载错误码配置
     */
    void loadErrorInfo();

    /*!
     * \brief 读取错误码文件
     */
    void readErroFile();

    /*!
     * \brief 读.pro以外的其他文件
     * \param strFileSrc 设备文件端路径
     * \param strFileDest 本地文件路径
     */
    int readFileOthers(const std::string &strFileSrc, const std::string &strFileDest, bool bCreat = false);

    /*!
     * \brief 从控制器读取文件
     * \param strDataSrc 数据来源：目录或文件
     * \param strFileDest 目标文件
     */
    int readFileFromDev(const std::string &strDataSrc, const std::string &strFileDest, int16u nCmdId, bool bCreat = false);

    /*!
     * \brief 解析错误码文件
     * \param strPath 文件路径
     * \param strPath 每解析成功一条告警信息是否触发新增告警的通知
     */
    bool parseErroFile(const std::string &strPath, bool isNotify = false);

    /*!
     * \brief 文件标识置为已读
     */
    int writeErroFileMark(int nMark = 1);

    /*!
     * \brief 清除历史故障
     */
    int writeHisWarning(int nLineFlg = 0);

    /*!
     * \brief 添加告警信息
     */
    void addWarnRecord(const std::string &content, bool isNotify);

    /**
     * @brief 根据错误码获取描述
     * @param strErrid 16进制字符串 不含"0x"
     * @param isRecord 是否打印日志类型，日志不打印行号
     */
    std::string getWarnContent(std::string strErrid, bool isRecord = false);

    /**
     * @brief 判定是否处于数据流模式
     */
    bool isAPIDataStream();

    /**
     * @brief 读取DSP报警行号
     */
    int readDSPWaringNo(int16s &dspWaringNo);

    /**
     * @brief 读取报警码解析表格文件
     * @param filePath 文件路径
     * @param errInfoMap 报警码映射表
     * @return
     */
    int readErroMapFromFile(const std::string &filePath, std::unordered_map<std::string, std::string> &errInfoMap);

    // 依赖注入的IdataService，基于老代码与控制器通信
    IDataSrvBase *_pDataService = nullptr;

    // 工程
    IProject *_pProject = nullptr;

    // 连接
    IConnection *_pConnection = nullptr;

    // 控制器调度器
    IRCScheduler *_pScheduler = nullptr;

    IRCConfig *_pConfig = nullptr;

    IMonitor *_pMonitor = nullptr;
    // 工艺指针
    IInoRobPluginMasterService *_pluginMasterService = nullptr;

    // 是否使能控制器报警信息监控
    bool _isEnable = false;

    // 是否正在读文件
    // bool _onReadFile = false;

    // 告警信息列表
    std::vector<WarnData> _warnList;

    // 去重判断
    std::unordered_set<std::string> _unRepeat;

    // 错误码-描述
    std::unordered_map<std::string, std::string> _errInfoMap;

    // 是否成功加载错误码配置文件
    bool _hadLoadErrInfo = false;
	
	bool _languageChangeNeedReadErrorRecordAgagin = true;
private slots:
    void onLanguageChanged(const std::string &language);
};
}  // namespace InoRobBusiness
