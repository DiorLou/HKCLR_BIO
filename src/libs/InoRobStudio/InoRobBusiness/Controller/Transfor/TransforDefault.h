#pragma once
#include <string>
#include "IInoRobBusiness.h"

namespace InoRobBusiness
{
class INOROBBUSINESS_CLASS TransforDefault : public ITransfor
{
    Q_OBJECT

public:
    TransforDefault(string name, IDataSrvBase *pDataSrv, QObject *parent = nullptr);
    virtual ~TransforDefault();

public:
    virtual void initParseDll(IProject *pProject) override;
    virtual void setRobotInformation(uint axisNum, const std::string &robotName) override;
    virtual bool parseProject(const std::string taskFilePaths[MAX_TASK_NUM], Project_Info *pInfo) override;
    virtual bool parseProgram(const std::string &taskFilePath, PraseInfo *pInfo) override;
    virtual bool parseTempProgram(const std::string &programFilePath, std::vector<std::string> &proArr) override;

    virtual int syncProjectInfo(std::string ctrlPath, signed char flags[SYNC_TYPE_NUMBER]) override;
    virtual int readCtrlProjectParseFlag(ParseStatus &flag) override;
    virtual bool waitForCtrlParseResult() override;
    virtual int readCtrlProjectNeedTrans(ParseDemand &flag) override;

    virtual bool isTrueLine(std::string cmdString) override;

    void getStmtNote(std::string cmdString, STMT_NOTE **pStmt) override;

    virtual ValueKind getVarValueKindAndRangeForRobotLab(char *varName, double range[2]) override;

    virtual void clearLineVarTable() override;
    virtual bool updateLineVarInfos(const std::string &proFileName, int lineNo, int taskId) override;
    virtual std::vector<VarInLineInfo_stu> getSelectedLineVarInfos() override;

    virtual void clearAllTable() override;
    virtual void updateVarNames(const std::string &proFileName, int lineNo, bool forceRefresh) override;
    virtual std::vector<std::string> getAllVarNames() override;
    virtual std::vector<std::string> getGlobalVarNames() override;
    virtual std::vector<std::string> getLocalVarNames() override;
    virtual std::vector<std::string> getModuleVarNames() override;
    virtual std::vector<std::string> getModuleNames() override;
    virtual std::vector<std::string> getStringVarNames() override;
    virtual std::vector<std::string> getBoolVarNames() override;
    virtual std::vector<std::string> getByteVarNames() override;
    virtual std::vector<std::string> getIntVarNames() override;
    virtual std::vector<std::string> getFloatVarNames() override;
    virtual std::vector<std::string> getDoubleVarNames() override;
    virtual std::vector<std::string> getStructVarNames() override;
    virtual std::vector<std::string> getStructNames() override;
    virtual std::vector<std::string> getSpeedNames() override;
    virtual std::vector<ArrayVarInfo_stu> getArrayVarNames() override;
    virtual std::vector<std::string> getCurveVarNames() override;
    virtual std::vector<std::string> getFileHandleVarNames() override;
    virtual std::vector<std::string> getFileDirHandleVarNames() override;

    virtual std::map<std::string, int> getStructInfos() override;

    virtual std::vector<SyntaxInfo> getFunctionInfos(const std::string &module, const std::string &filePath) override;
    virtual std::vector<FunctionInfo> getFunctionParamTypes() override;
    virtual std::vector<SyntaxInfo> getCurveInfos() override;
    virtual std::vector<FunctionInfo> getCurveParamTypes() override;

    virtual PraseALineInfo *praseLineDegree(const std::string &cmdstring) override;

    virtual bool getCmdPointInfo(const std::string &programFileName, int lineNo,
                                 PointType &pointType, int &pointNo, int &toolNo, int &wobjNo) override;

    virtual void addLabel(const std::string &labelName, const std::string &realName) override;
    virtual void refreshLabels() override;
    virtual void clearLables() override;

    virtual bool isKeyWord(const std::string &str) override;

    virtual void setPrintSwitch(bool isPrint) override;

    virtual bool getLineNumFromModeName(const std::string &pNowModelName, int &lineNum) override;

    virtual bool getCmdPointInfoTW(const std::string &pNowModelName, int lineNo,
                                   int &pointType, int &pointLeftNo, int &pointRightNo, int &wobjNo, int &toolNo) override;

    virtual int getTaskAllProName(int TaskNo, std::string pProName[MAX_QUE_SIZE]) override;

    virtual bool isTransforWorking() override;

    virtual int isCanSetRunLineNo(const std::string &pNowModelName, int lineNo) override;

private:
    /// <summary>
    /// 解析从译码库获取的函数信息
    /// </summary>
    /// <param name="syntaxInfos">输入，函数信息集合</param>
    /// <returns>解析后的函数信息集合，包含函数名称、函数参数类型和参数名称集合</returns>
    std::vector<FunctionInfo> PraseSyntaxInfos(const std::vector<SyntaxInfo> &syntaxInfos);

    /**
     * @brief 等待译码库处理完成，因为译码库滥用全局变量，线程不安全，同时调用接口的时候会触发崩溃
     * 因此这个类封装的所有译码库设置和触发处理的接口在开头都必须先执行这个函数，避免崩溃情况发生
     * @param funcName 输入，函数名称，用于日志记录
     */
    bool waitTransforWorkFinished(const std::string &funcName);

private:
    IDataSrvBase *_pDataSrv = nullptr;
};
}  // namespace InoRobBusiness
