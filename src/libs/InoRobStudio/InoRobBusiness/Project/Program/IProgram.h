#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "dllspec.h"
#include "GlobalDataTypes.h"
#include "../Project/ProjectHelper.h"

/// <summary>
/// 程序文件处理基类
/// </summary>
class INOROBBUSINESS_CLASS IProgram : public QObject
{
    Q_OBJECT

public:
    /// <summary>
    /// 虚析构函数，确保指针对象释放时，该类的资源能被释放
    /// </summary>
    virtual ~IProgram()
    {
    }

    /**
     * @brief 设置工程的文件操作模式
     */
    virtual void setProjectOperateMode(ProjectFileOperateMode mode) = 0;
    /// <summary>
    /// 设置控制器ip地址(依赖注入)
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    virtual void SetControllerIp(const std::string &ip) = 0;
    /// <summary>
    /// 设置当前加载的工程名称(依赖注入)
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    virtual void SetProjectName(const std::string &name) = 0;

    /**
     * @brief 设置工程类型
     * @param type 输入，工程类型
     */
    virtual void setProjectType(ProjectType type) = 0;
    /**
     * @brief  是否被修改过，
     不传参则有任意一个程序文件被修改了，都会返回true，
     传入具体的程序文件名称，则只查询这个程序文件的修改状态
     * @param name 输入，程序文件名称
    */
    virtual bool isModified() = 0;
    virtual bool isModified(const std::string &name) = 0;
    /**
     * @brief 设置修改状态
     * @param name 输入，程序文件名称
     * @param state 输入，修改状态
     */
    virtual void setModifyState(const std::string &name, bool state) = 0;
    /**
     * @brief 清空程序文件修改状态记录
     */
    virtual void clearModifyStates() = 0;
    /// <summary>
    /// 从程序文件解析文件头信息
    /// </summary>
    /// <param name="fileInfo">输出，文件头信息</param>
    /// <param name="name">输入，程序文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ReadProgramFileInfo(ProjectFileInfo &fileInfo, const std::string &name) = 0;
    /// <summary>
    /// 从文件解析程序数据
    /// </summary>
    /// <param name="posArr">输出，局部点位数据</param>
    /// <param name="proArr">输出，程序文本</param>
    /// <param name="path">输入，文件路径</param>
    /// <param name="cacheOrNot">输入，是否把程序文件数据缓存，默认不缓存（缓存通常用于记录页面数据，用于后面的addProgramLines等函数接口）</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ReadProgram(std::vector<MRobPosItem> &posArr, std::vector<string> &proArr, const std::string &name, bool cacheOrNot = false) = 0;
    /// <summary>
    /// 将程序数据写入到文件
    /// </summary>
    /// <param name="path">输入，文件名称(带后缀)</param>
    /// <param name="posArr">输入，局部点位数据</param>
    /// <param name="proArr">输入，程序文本</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SaveProgram(const std::string &name, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr, bool isNeedEditMode = true) = 0;
    /**
     * @brief 热调点模式将程序数据写入到文件
     * @param name 输入，文件名称
     * @param posArr 输入，局部点位数据
     * @param proArr 输入，程序文本
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveProgramRT(const std::string &name, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr) = 0;
    /**
     * @brief 将程序数据写入到文件
     * @param name 输入，文件名称(带后缀)
     * @param posArr 输入，局部点位数据
     * @param proArr 输入，程序文本
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveLocalFile(const std::string &name, const std::vector<MRobPosItem> &posArr, const std::vector<string> &proArr) = 0;
    /**
     * @brief 获取当前加载工程中指定名称的程序文件的本地路径
     * @param name 输入，文件名称(带后缀)
     */
    virtual std::string getLocalFilePath(const std::string &name) = 0;
    /// <summary>
    /// 获取默认的程序文件名称
    /// </summary>
    /// <param name="infos">输入，程序文件名称集合</param>
    /// <param name="baseName">输入，基础名称字段，为空的话默认返回新建默认名称</param>
    /// <returns>默认的工程名称</returns>
    virtual std::string NewProgramDefaultName(std::vector<std::string> &names, std::string baseName = "") = 0;
    /// <summary>
    /// 获取不带后缀的程序文件名称
    /// </summary>
    /// <param name="name">输入，程序文件名称</param>
    /// <returns>不带后缀的程序文件名称</returns>
    virtual std::string FileNameWithoutExtension(const std::string &name) = 0;
    /// <summary>
    /// 检查程序文件名称是否合法，全面的检查
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="name">输入，名称</param>
    /// <returns>是true，否false</returns>
    virtual bool IsProgramFileNameValid(std::string &errMsg, const std::string &name) = 0;
    /// <summary>
    /// 新建程序文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int NewFile(const std::string &name, const ProgramType &type) = 0;
    /// <summary>
    /// 复制程序文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    virtual void SetCopyFile(const std::string &name) = 0;
    /// <summary>
    /// 获取待粘贴的程序文件名称
    /// </summary>
    virtual std::string GetCopiedName() = 0;
    /// <summary>
    /// 粘贴程序文件
    /// </summary>
    /// <param name="srcName">输入，原名称</param>
    /// <param name="targetName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int PasteFile(const std::string &srcName, const std::string &targetName) = 0;
    /// <summary>
    /// 重命名程序文件
    /// </summary>
    /// <param name="oldName">输入，旧名称</param>
    /// <param name="newName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int RenameFile(const std::string &oldName, const std::string &newName) = 0;
    /// <summary>
    /// 删除程序文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int DelFile(const std::string &name) = 0;
    /// <summary>
    /// 导入程序文件
    /// </summary>
    /// <param name="paths">输入，程序文件路径集合</param>
    /// <param name="realImportFileNames">输出，实际添加到工程中的程序文件名称集合</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ImportFiles(const std::vector<std::string> &paths) = 0;
    virtual int ImportFiles(const std::vector<std::string> &paths, std::vector<std::string> &realImportFileNames) = 0;
    /// <summary>
    /// 导出程序文件
    /// </summary>
    /// <param name="names">输入，待导出的程序文件名称集合</param>
    /// <param name="folder">输入，目标文件夹</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ExportFiles(const std::vector<std::string> &names, const std::string &folder) = 0;

    /**
     * @brief 从程序文本缓存中删除对应的程序文本数据
     * @param fileName 输入，程序文件名称
     */
    virtual void delProgramBuffer(const std::string &fileName) = 0;
    /**
     * @brief 向缓存中指定程序文本插入若干行文本
     * @param fileName 输入，程序文件名称
     * @param lineNoArr 输入，若干行文本对应的行号集合
     * @param lines 输入，若干行文本集合
     * @return 成功返回0，其他请见错误码
     */
    virtual int insertProgramLines(const std::string &fileName, int lineNo, const std::vector<std::string> &lines) = 0;
    /**
     * @brief 修改缓存中指定程序文本的若干行文本
     * @param fileName 输入，程序文件名称
     * @param lineNoArr 输入，若干行文本对应的行号集合
     * @param lines 输入，若干行文本集合
     * @return 成功返回0，其他请见错误码
     */
    virtual int changeProgramLines(const std::string &fileName, const std::vector<int> &lineNoArr, const std::vector<std::string> &lines) = 0;
    /**
     * @brief 删除缓存中指定程序文本的若干行文本
     * @param fileName 输入，程序文件名称
     * @param lineNoArr 输入，若干行文本对应的行号集合
     * @return 成功返回0，其他请见错误码
     */
    virtual int delProgramLines(const std::string &fileName, const std::vector<int> &lineNoArr) = 0;
    /**
     * @brief 保存缓存中指定名称的程序数据（指令文本和局部点位）
     * @param fileName 输入，程序文件名称
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveProgramBuffer(const std::string &fileName) = 0;
    /**
     * @brief 保存缓存中所有的程序数据（指令文本和局部点位）
     * @return 成功返回0，其他请见错误码
     */
    virtual int saveAllProgramBuffer() = 0;

    /// <summary>
    /// 添加页面点位数据到缓存中
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="points">输入，点位数据</param>
    virtual void AddViewPoints(const std::string &fileName, const std::vector<MRobPosItem> &points) = 0;
    /// <summary>
    /// 从点位数据缓存中删除对应的点位数据
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    virtual void DelViewPoints(const std::string &fileName) = 0;
    /**
     * @brief 点位缓存中是否存在对应点位文件名称的数据
     */
    virtual bool isViewPointsExisted(const std::string &fileName) = 0;
    /**
     * @brief 获取对应文件中可用点位序号
     * @param fileName 输入，文件名称
     * @param isTip 输入，是否提示点位达到上限
     * @return 有可用则返回0~9999范围内可用的序号，没有可用的则返回-1
     */
    virtual int getAvailablePointNo(const std::string &fileName, bool isTip = true) = 0;
    /// <summary>
    /// 新增点
    /// </summary>
    /// <param name="index">输出，新增点的序号</param>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="point">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int AddPoint(int &index, const std::string &fileName, MRobPosItem &point) = 0;
    /**
     * @brief 新增点（此接口需要使用前先确定点位数据，如序号等）
     * @param fileName 输入，点位文件名称
     * @param point输入，点位数据
     * @return 成功返回0，其他请见错误码
     */
    virtual int addPoint(const std::string &fileName, const MRobPosItem &point) = 0;
    /// <summary>
    /// 修改点位数据
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="point">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ChangePoint(const std::string &fileName, const MRobPosItem &point, bool isNeedEditMode = true) = 0;
    /**
     * @brief 热调点模式下修改点位数据
     * @param fileName 输入，程序文件名称
     * @param point 输入，点位数据
     * @return
     */
    virtual int changePointRT(const std::string &fileName, const MRobPosItem &point) = 0;
    /// <summary>
    /// 获取对应点位文件的点位数据
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <returns>点位数据</returns>
    virtual std::vector<MRobPosItem> GetPoints(const std::string &fileName) = 0;
    /// <summary>
    /// 获取对应点位文件，指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="indexs">输入，点位序号集合</param>
    /// <returns>点位数据</returns>
    virtual std::vector<MRobPosItem> GetPoints(const std::string &fileName, const std::vector<int> &indexs) = 0;
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>点位数据，失败则点位数据中的序号为-1</returns>
    virtual MRobPosItem GetPoint(const std::string &fileName, int index) = 0;
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>点位数据，失败则点位数据中的序号为-1</returns>
    virtual MRobPosItem GetPoint(const std::vector<MRobPosItem> &points, int index) = 0;
    /**
     * @brief 查询标签名是否已经存在
     * @param labelName 输入，标签名
     * @return true-存在，false-不存在
     */
    virtual bool isLabelExisted(const std::string &label) = 0;
    /**
     * @brief 添加标签名至缓存中
     * @param fileName 输入，程序文件名称
     * @param label 输入，标签名
     */
    virtual void addLabel(const std::string &fileName, const std::string &label) = 0;
    /**
     * @brief 替换缓存中已经存在的标签名
     * @param fileName 输入，程序文件名称
     * @param oldLabel 输入，待替换的旧标签名
     * @param newLabel 输入，将要替换成的新标签名
     */
    virtual void replaceLabel(const std::string &fileName, const std::string &oldLabel, const std::string &newLabel) = 0;
    /**
     * @brief 从缓存中删除指定的标签名
     * @param fileName 输入，程序文件名称
     * @param label 输入，标签名
     */
    virtual void delLabel(const std::string &fileName, const std::string &label) = 0;
    /**
     * @brief 清空标签缓存
     */
    virtual void clearLabels() = 0;
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    virtual int FindPoint(const std::string &fileName, int index) = 0;
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    virtual int FindPoint(const std::vector<MRobPosItem> &points, int index) = 0;
    /// <summary>
    /// 复制点位
    /// </summary>
    /// <param name="fileName">输入，待复制的点位所在的程序文件名称</param>
    /// <param name="indexs">输入，待复制的点位序号集合</param>
    virtual void CopyPoints(const std::string &fileName, const std::vector<int> &indexs) = 0;
    /// <summary>
    /// 粘贴点位
    /// </summary>
    /// <param name="indexs">输出，新增点的序号集合</param>
    /// <param name="fileName">输入，希望粘贴到的程序文件的名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int PastePoints(std::vector<int> &indexs, const std::string &fileName) = 0;
    /// <summary>
    /// 重新设置点位序号
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="srcIndex">输入，原点位序号</param>
    /// <param name="newIndex">输入，新点位序号</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int RenamePoint(const std::string &fileName, int srcIndex, int newIndex) = 0;
    /// <summary>
    /// 删除点位
    /// </summary>
    /// <param name="fileName">输入，程序文件名称</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int DelPoint(const std::string &fileName, int index) = 0;

    /**
     * @brief 批量改点 - 向控制器下发待修改点序号集合
     * @param param 输入，批量修改点相关参数
     * @param ptNoArr 输入，点位序号集合数据
     * @return 成功返回0，其他请见错误码
     */
    virtual int writeModifyPtsData(const ModifyPtsParam &param, const std::vector<unsigned short> &ptNoArr) = 0;
    /**
     * @brief 批量改点 - 读取控制器改点状态
     * @param status 输出，改点状态
     * @return 成功返回0，其他请见错误码
     */
    virtual int readModifyPtsStatus(ModifyPtsStatus &status) = 0;
};
