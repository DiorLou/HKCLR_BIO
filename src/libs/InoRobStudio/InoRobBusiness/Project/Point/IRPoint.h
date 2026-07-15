#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "../ProjectHelper.h"
#include "dllspec.h"

/// <summary>
/// 位置点位处理基类
/// </summary>
class INOROBBUSINESS_CLASS IRPoint : public QObject
{
    Q_OBJECT

public:
    virtual ~IRPoint()
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

    /// <summary>
    /// 默认位置点位文件名称
    /// </summary>
    virtual std::string DefaultFileName() = 0;
    /// <summary>
    /// 获取默认的全局位置点位文件名称
    /// </summary>
    /// <param name="infos">输入，全局位置点位文件名称集合</param>
    /// <param name="baseName">输入，基础名称字段，为空的话默认返回新建默认名称</param>
    /// <returns>默认的全局位置点位文件名称</returns>
    virtual std::string NewDefaultFileName(std::vector<std::string> &names, std::string baseName = "") = 0;

    /// <summary>
    /// 判断点位文件名称是否合法
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="fileName">输入，文件名称</param>
    /// <returns>合法true，非法false</returns>
    virtual bool IsPointFileNameValid(std::string &errMsg, const std::string &fileName) = 0;
    /// <summary>
    /// 新建全局位置点位文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int NewFile(const std::string &name) = 0;
    /// <summary>
    /// 复制全局位置点位文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    virtual void SetCopyFile(const std::string &name) = 0;
    /// <summary>
    /// 获取待粘贴的全局位置点位文件名称
    /// </summary>
    virtual std::string GetCopiedName() = 0;
    /// <summary>
    /// 粘贴全局位置点位文件
    /// </summary>
    /// <param name="srcName">输入，原名称</param>
    /// <param name="targetName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int PasteFile(const std::string &srcName, const std::string &targetName) = 0;
    /// <summary>
    /// 重命名全局位置点位文件
    /// </summary>
    /// <param name="oldName">输入，旧名称</param>
    /// <param name="newName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int RenameFile(const std::string &oldName, const std::string &newName) = 0;
    /// <summary>
    /// 删除全局位置点位文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int DelFile(const std::string &name) = 0;
    /// <summary>
    /// 导入全局位置点位文件
    /// </summary>
    /// <param name="paths">输入，全局位置点位文件路径集合</param>
    /// <param name="realImportFileNames">输出，实际添加到工程中的全局位置点位文件名称集合</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ImportFiles(const std::vector<std::string> &paths) = 0;
    virtual int ImportFiles(const std::vector<std::string> &paths, std::vector<std::string> &realImportFileNames) = 0;
    /// <summary>
    /// 导出全局位置点位文件
    /// </summary>
    /// <param name="names">输入，待导出的全局位置点位文件名称集合</param>
    /// <param name="folder">输入，目标文件夹</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ExportFiles(const std::vector<std::string> &names, const std::string &folder) = 0;

    /**
     * @brief  是否被修改过，
     不传参则有任意一个点文件被修改了，都会返回true，
     传入具体的点文件名称，则只查询这个点文件的修改状态
     * @param name 输入，点文件名称
    */
    virtual bool isModified() = 0;
    virtual bool isModified(const std::string &name) = 0;
    /**
     * @brief 设置修改状态
     * @param name 输入，点文件名称
     * @param state 输入，修改状态
     */
    virtual void setModifyState(const std::string &name, bool state) = 0;
    /**
     * @brief 清空点文件修改状态记录
     */
    virtual void clearModifyStates() = 0;
    /// <summary>
    /// 读取点位文件数据
    /// </summary>
    /// <param name="points">输出，点位数据</param>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="isAlwaysFromFile">输入，是否始终从文件读取</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int readPoints(const std::string &fileName) = 0;
    virtual int ReadPoints(std::vector<MRobPosItem> &points, const std::string &fileName, bool isAlwaysFromFile = false) = 0;
    /// <summary>
    /// 保存点位数据到点位文件中
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="points">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SavePoints(const std::string &fileName, std::vector<MRobPosItem> &points, bool isNeedEditMode = true) = 0;
    /// <summary>
    /// 保存指定名称的页面缓存的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SaveViewPoints(const std::string &fileName, bool isNeedEditMode = true) = 0;
    /**
     * @brief 热调点模式保存点位数据到点位文件中
     * @param fileName 输入，点位文件名称
     * @param points 输入，点位数据
     * @return
     */
    virtual int SavePointsRT(const std::string &fileName, std::vector<MRobPosItem> &points) = 0;
    /**
     * @brief 热调点模式保存指定名称的页面缓存的点位数据
     * @param fileName 输入，点位文件名称
     * @return
     */
    virtual int saveViewPointsRT(const std::string &fileName) = 0;
    /// <summary>
    /// 保存所有页面缓存的点位数据
    /// </summary>
    /// <returns>>成功返回0，其他请见错误码</returns>
    virtual int SaveAllViewPoints() = 0;
    /// <summary>
    /// 添加页面点位数据到缓存中
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="points">输入，点位数据</param>
    virtual void AddViewPoints(const std::string &fileName, const std::vector<MRobPosItem> &points) = 0;
    /// <summary>
    /// 从点位数据缓存中删除对应的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    virtual void DelViewPoints(const std::string &fileName) = 0;
    /**
     * @brief 清空页面点位数据的缓存
     */
    virtual void clearViewPoints() = 0;
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
    /// <param name="fileName">输入，点位文件名称</param>
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
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="point">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ChangePoint(const std::string &fileName, const MRobPosItem &point, bool isNeedEditMode = true) = 0;
    /**
     * @brief 热调点模式修改点位数据
     * @param fileName 输入，点位文件名称
     * @param point 输入，点位数据
     * @return
     */
    virtual int changePointRT(const std::string &fileName, const MRobPosItem &point) = 0;
    /// <summary>
    /// 获取对应点位文件的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>点位数据</returns>
    virtual std::vector<MRobPosItem> GetPoints(const std::string &fileName) = 0;
    /// <summary>
    /// 获取对应点位文件，指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="indexs">输入，点位序号集合</param>
    /// <returns>点位数据</returns>
    virtual std::vector<MRobPosItem> GetPoints(const std::string &fileName, const std::vector<int> &indexs) = 0;
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
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
     * @brief 获取标签名集合
     */
    virtual std::vector<std::string> getLabels() = 0;
    /**
     * @brief 初始化标签数组缓存，初始化为10000个空字符串元素的set数组
     */
    virtual void initLabels() = 0;
    /**
     * @brief 替换缓存中已经存在的标签名
     * @param pointNo 输入，点位序号
     * @param newLabel 输入，将要替换成的新标签名
     */
    virtual void replaceLabel(int pointNo, const std::string &newLabel) = 0;
    /**
     * @brief 获取指定点位序号的点位标签
     * @param pointNo 输入，点位序号
     * @return 点位标签
     */
    virtual std::string getLabel(int pointNo) = 0;
    /**
     * @brief 获取指定序号的点位的标签和备注
     * @param fileName 输入，点位文件名称
     * @param index 输入，点位序号
     * @return 对应序号的点位的标签和备注，如果失败，则结构体中点位序号为-1
     */
    virtual PtLabelAndDes getLabelAndDescription(const std::string &fileName, int index) = 0;
    /**
     * @brief 获取指定序号区间的点位的标签和备注集合
     * @param fileName 输入，点位文件名称
     * @param startNo 输入，点位在数组中的起始下标(不是指点位的序号)
     * @param endNo 输入，点位在数组中的结束下标(不是指点位的序号)
     * @return 对应序号区间的点位的标签和备注集合，如果失败，则容器数组为空
     */
    virtual std::vector<PtLabelAndDes> getLabelsAndDescriptions(const std::string &fileName, int startNo, int endNo) = 0;
    /**
     * @brief 获取指定点位文件的所有点位的标签和备注集合
     * @param fileName 输入，点位文件名称
     * @return 对应点位文件的所有点位的标签和备注集合，如果失败，则容器数组为空
     */
    virtual std::vector<PtLabelAndDes> getAllLabelsAndDescriptions(const std::string &fileName) = 0;
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="pointNo">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    virtual int FindPoint(const std::string &fileName, int pointNo) = 0;
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="pointNo">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    virtual int FindPoint(const std::vector<MRobPosItem> &points, int pointNo) = 0;
    /// <summary>
    /// 复制点位
    /// </summary>
    /// <param name="fileName">输入，待复制的点位所在的点位文件名称</param>
    /// <param name="indexs">输入，待复制的点位序号集合</param>
    virtual void CopyPoints(const std::string &fileName, const std::vector<int> &indexs) = 0;
    /// <summary>
    /// 粘贴点位
    /// </summary>
    /// <param name="indexs">输出，新增点的序号集合</param>
    /// <param name="fileName">输入，希望粘贴到的点位文件的名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int PastePoints(std::vector<int> &indexs, const std::string &fileName) = 0;
    /// <summary>
    /// 重新设置点位序号
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="srcIndex">输入，原点位序号</param>
    /// <param name="newIndex">输入，新点位序号</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int RenamePoint(const std::string &fileName, int srcIndex, int newIndex) = 0;
    /// <summary>
    /// 删除点位
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
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
    /**
     * @brief 批量改点 - 整个流程
     * @param status 输出，改点状态
     * @param ptNoData 输入，点位序号集合数据
     * @param offsetData 输入，点位偏移量
     * @return 成功返回0，其他请见错误码
     */
    virtual int modifyPts(ModifyPtsStatus &status, const std::vector<unsigned short> &ptNoData, const ModifyPtsParam &param) = 0;
    /**
     * @brief 批量改点 - 清空当前记录的点位总偏移量
     */
    virtual void clearPointOffsets() = 0;
    /**
     * @brief 批量改点 - 获取当前记录的点位总偏移量
     */
    virtual std::vector<PointOffset> getPointOffsets() = 0;
};
