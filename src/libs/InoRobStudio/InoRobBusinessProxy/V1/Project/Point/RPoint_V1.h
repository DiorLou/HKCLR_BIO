#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"
#include "../ProjectHelper_V1.h"
#include "../../GlobalDataTypes_V1.h"

using namespace InoRobBusiness;

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS RPoint_V1
{
#pragma region 构造与析构

private:
    IRPoint *_rPoint = nullptr;

public:
    RPoint_V1(IRPoint *rPoint);
    ~RPoint_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    /**
     * @brief 设置工程的文件操作模式
     */
    void setProjectOperateMode(ProjectFileOperateMode_V1 mode);
    /// <summary>
    /// 设置控制器ip地址(依赖注入)
    /// </summary>
    /// <param name="ip">输入，控制器ip</param>
    void SetControllerIp(const std::string &ip);
    /// <summary>
    /// 设置当前加载的工程名称(依赖注入)
    /// </summary>
    /// <param name="name">输入，工程名称</param>
    void SetProjectName(const std::string &name);
    /// <summary>
    /// 默认位置点位文件名称
    /// </summary>
    std::string DefaultFileName();
    /// <summary>
    /// 获取默认的全局位置点位文件名称
    /// </summary>
    /// <param name="infos">输入，全局位置点位文件名称集合</param>
    /// <param name="baseName">输入，基础名称字段，为空的话默认返回新建默认名称</param>
    /// <returns>默认的全局位置点位文件名称</returns>
    std::string NewDefaultFileName(std::vector<std::string> &names, std::string baseName = "");
    /// <summary>
    /// 判断点位文件名称是否合法
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="fileName">输入，文件名称</param>
    /// <returns>合法true，非法false</returns>
    bool IsPointFileNameValid(std::string &errMsg, const std::string &fileName);
    /// <summary>
    /// 新建全局位置点位文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int NewFile(const std::string &name);
    /// <summary>
    /// 复制全局位置点位文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    void SetCopyFile(const std::string &name);
    /// <summary>
    /// 获取待粘贴的全局位置点位文件名称
    /// </summary>
    std::string GetCopiedName();
    /// <summary>
    /// 粘贴全局位置点位文件
    /// </summary>
    /// <param name="srcName">输入，原名称</param>
    /// <param name="targetName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int PasteFile(const std::string &srcName, const std::string &targetName);
    /// <summary>
    /// 重命名全局位置点位文件
    /// </summary>
    /// <param name="oldName">输入，旧名称</param>
    /// <param name="newName">输入，新名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int RenameFile(const std::string &oldName, const std::string &newName);
    /// <summary>
    /// 删除全局位置点位文件
    /// </summary>
    /// <param name="name">输入，文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int DelFile(const std::string &name);
    /// <summary>
    /// 导入全局位置点位文件
    /// </summary>
    /// <param name="paths">输入，全局位置点位文件路径集合</param>
    /// <param name="realImportFileNames">输出，实际添加到工程中的全局位置点位文件名称集合</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ImportFiles(const std::vector<std::string> &paths);
    int ImportFiles(const std::vector<std::string> &paths, std::vector<std::string> &realImportFileNames);
    /// <summary>
    /// 导出全局位置点位文件
    /// </summary>
    /// <param name="names">输入，待导出的全局位置点位文件名称集合</param>
    /// <param name="folder">输入，目标文件夹</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ExportFiles(const std::vector<std::string> &names, const std::string &folder);
    /**
     * @brief  是否被修改过，
     不传参则有任意一个点文件被修改了，都会返回true，
     传入具体的点文件名称，则只查询这个点文件的修改状态
     * @param name 输入，点文件名称
    */
    bool isModified();
    bool isModified(const std::string &name);
    /**
     * @brief 设置修改状态
     * @param name 输入，点文件名称
     * @param state 输入，修改状态
     */
    void setModifyState(const std::string &name, bool state);
    /**
     * @brief 清空点文件修改状态记录
     */
    void clearModifyStates();
    /// <summary>
    /// 读取点位文件数据
    /// </summary>
    /// <param name="points">输出，点位数据</param>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int readPoints(const std::string &fileName);
    int ReadPoints(std::vector<MRobPosItem_V1> &points, const std::string &fileName);
    /// <summary>
    /// 保存点位数据到点位文件中
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="points">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int SavePoints(const std::string &fileName, std::vector<MRobPosItem_V1> &points);
    /// <summary>
    /// 保存指定名称的页面缓存的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int SaveViewPoints(const std::string &fileName);
    /// <summary>
    /// 保存所有页面缓存的点位数据
    /// </summary>
    /// <returns>>成功返回0，其他请见错误码</returns>
    int SaveAllViewPoints();
    /// <summary>
    /// 添加页面点位数据到缓存中
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="points">输入，点位数据</param>
    void AddViewPoints(const std::string &fileName, const std::vector<MRobPosItem_V1> &points);
    /// <summary>
    /// 从点位数据缓存中删除对应的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    void DelViewPoints(const std::string &fileName);
    /**
     * @brief 点位缓存中是否存在对应点位文件名称的数据
     */
    bool isViewPointsExisted(const std::string &fileName);
    /**
     * @brief 清空页面点位数据缓存
     */
    void clearViewPoints();
    /**
     * @brief 获取对应文件中可用点位序号
     * @param fileName 输入，文件名称
     * @param isTip 输入，是否提示点位达到上限
     * @return 有可用则返回0~9999范围内可用的序号，没有可用的则返回-1
     */
    int getAvailablePointNo(const std::string &fileName, bool isTip = true);
    /// <summary>
    /// 新增点
    /// </summary>
    /// <param name="index">输出，新增点的序号</param>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="point">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int AddPoint(int &index, const std::string &fileName, MRobPosItem_V1 &point);
    /**
     * @brief 新增点（此接口需要使用前先确定点位数据，如序号等）
     * @param fileName 输入，点位文件名称
     * @param point输入，点位数据
     * @return 成功返回0，其他请见错误码
     */
    int addPoint(const std::string &fileName, const MRobPosItem_V1 &point);
    /// <summary>
    /// 修改点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="point">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int ChangePoint(const std::string &fileName, const MRobPosItem_V1 &point);
    /// <summary>
    /// 获取对应点位文件的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>点位数据</returns>
    std::vector<MRobPosItem_V1> GetPoints(const std::string &fileName);
    /// <summary>
    /// 获取对应点位文件，指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="indexs">输入，点位序号集合</param>
    /// <returns>点位数据</returns>
    std::vector<MRobPosItem_V1> GetPoints(const std::string &fileName, const std::vector<int> &indexs);
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>点位数据，失败则点位数据中的序号为-1</returns>
    MRobPosItem_V1 GetPoint(const std::string &fileName, int index);
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>点位数据，失败则点位数据中的序号为-1</returns>
    MRobPosItem_V1 GetPoint(const std::vector<MRobPosItem_V1> &points, int index);
    /**
     * @brief 查询标签名是否已经存在
     * @param labelName 输入，标签名
     * @return true-存在，false-不存在
     */
    bool isLabelExisted(const std::string &label);
    /**
     * @brief 获取标签名集合
     */
    std::vector<std::string> getLabels();
    /**
     * @brief 初始化标签数组缓存，初始化为10000个空字符串元素的set数组
     */
    void initLabels();
    /**
     * @brief 替换缓存中已经存在的标签名
     * @param pointNo 输入，点位序号
     * @param newLabel 输入，将要替换成的新标签名
     */
    void replaceLabel(int pointNo, const std::string &newLabel);
    /**
     * @brief 获取指定点位序号的点位标签
     * @param pointNo 输入，点位序号
     * @return 点位标签
     */
    std::string getLabel(int pointNo);
    /**
     * @brief 获取指定序号的点位的标签和备注
     * @param fileName 输入，点位文件名称
     * @param index 输入，点位序号
     * @return 对应序号的点位的标签和备注，如果失败，则结构体中点位序号为-1
     */
    PtLabelAndDes_V1 getLabelAndDescription(const std::string &fileName, int index);
    /**
     * @brief 获取指定序号区间的点位的标签和备注集合
     * @param fileName 输入，点位文件名称
     * @param startNo 输入，点位在数组中的起始下标(不是指点位的序号)
     * @param endNo 输入，点位在数组中的结束下标(不是指点位的序号)
     * @return 对应序号区间的点位的标签和备注集合，如果失败，则容器数组为空
     */
    std::vector<PtLabelAndDes_V1> getLabelsAndDescriptions(const std::string &fileName, int startNo, int endNo);
    /**
     * @brief 获取指定点位文件的所有点位的标签和备注集合
     * @param fileName 输入，点位文件名称
     * @return 对应点位文件的所有点位的标签和备注集合，如果失败，则容器数组为空
     */
    std::vector<PtLabelAndDes_V1> getAllLabelsAndDescriptions(const std::string &fileName);
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="pointNo">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    int FindPoint(const std::string &fileName, int pointNo);
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="pointNo">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    int FindPoint(const std::vector<MRobPosItem_V1> &points, int pointNo);
    /// <summary>
    /// 复制点位
    /// </summary>
    /// <param name="fileName">输入，待复制的点位所在的点位文件名称</param>
    /// <param name="indexs">输入，待复制的点位序号集合</param>
    void CopyPoints(const std::string &fileName, const std::vector<int> &indexs);
    /// <summary>
    /// 粘贴点位
    /// </summary>
    /// <param name="indexs">输出，新增点的序号集合</param>
    /// <param name="fileName">输入，希望粘贴到的点位文件的名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int PastePoints(std::vector<int> &indexs, const std::string &fileName);
    /// <summary>
    /// 重新设置点位序号
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="srcIndex">输入，原点位序号</param>
    /// <param name="newIndex">输入，新点位序号</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int RenamePoint(const std::string &fileName, int srcIndex, int newIndex);
    /// <summary>
    /// 删除点位
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    int DelPoint(const std::string &fileName, int index);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
