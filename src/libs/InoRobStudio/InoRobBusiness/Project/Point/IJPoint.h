#pragma once
#include <string>
#include <vector>
#include <QObject>
#include "../ProjectHelper.h"
#include "dllspec.h"

/// <summary>
/// 关节点位处理基类
/// </summary>
class INOROBBUSINESS_CLASS IJPoint : public QObject
{
    Q_OBJECT

public:
    virtual ~IJPoint()
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
    /// 默认点位文件名称
    /// </summary>
    virtual std::string DefaultFileName() = 0;

    /// <summary>
    /// 判断点位文件名称是否合法
    /// </summary>
    /// <param name="errMsg">输出，错误信息</param>
    /// <param name="fileName">输入，文件名称</param>
    /// <returns>合法true，非法false</returns>
    virtual bool IsPointFileNameValid(std::string &errMsg, const std::string &fileName) = 0;

    /// <summary>
    /// 导入程序文件
    /// </summary>
    /// <param name="paths">输入，程序文件路径集合</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ImportFiles(const std::vector<std::string> &paths) = 0;
    /// <summary>
    /// 导出程序文件
    /// </summary>
    /// <param name="names">输入，待导出的程序文件名称集合</param>
    /// <param name="folder">输入，目标文件夹</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ExportFiles(const std::vector<std::string> &names, const std::string &folder) = 0;

    /**
     * @brief  是否被修改过
     */
    virtual bool isModified() = 0;
    /**
     * @brief 设置修改状态
     * @param state 输入，修改状态
     */
    virtual void setModifyState(bool state) = 0;
    /// <summary>
    /// 读取点位文件数据
    /// </summary>
    /// <param name="points">输出，点位数据</param>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int readPoints(const std::string &fileName, bool isAlwaysFromFile = false) = 0;
    virtual int ReadPoints(std::vector<MJPosItem> &points, const std::string &fileName, bool isAlwaysFromFile = false) = 0;
    /// <summary>
    /// 保存点位数据到点位文件中
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="points">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SavePoints(const std::string &fileName, const std::vector<MJPosItem> &points, bool isNeedEditMode = true) = 0;
    /// <summary>
    /// 保存指定名称的页面缓存的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int SaveViewPoints(const std::string &fileName, bool isNeedEditMode = true) = 0;
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
    virtual void AddViewPoints(const std::string &fileName, const std::vector<MJPosItem> &points) = 0;
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
    virtual int AddPoint(int &index, const std::string &fileName, MJPosItem &point) = 0;
    /**
     * @brief 新增点（此接口需要使用前先确定点位数据，如序号等）
     * @param fileName 输入，点位文件名称
     * @param point输入，点位数据
     * @return 成功返回0，其他请见错误码
     */
    virtual int addPoint(const std::string &fileName, const MJPosItem &point) = 0;
    /// <summary>
    /// 修改点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="point">输入，点位数据</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int ChangePoint(const std::string &fileName, const MJPosItem &point, bool isNeedEditMode = true) = 0;
    /// <summary>
    /// 获取对应点位文件的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <returns>点位数据</returns>
    virtual std::vector<MJPosItem> GetPoints(const std::string &fileName) = 0;
    /// <summary>
    /// 获取对应点位文件，指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="indexs">输入，点位序号集合</param>
    /// <returns>点位数据</returns>
    virtual std::vector<MJPosItem> GetPoints(const std::string &fileName, const std::vector<int> &indexs) = 0;
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="fileName">输入，点位文件名称</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>点位数据，失败则点位数据中的序号为-1</returns>
    virtual MJPosItem GetPoint(const std::string &fileName, int index) = 0;
    /// <summary>
    /// 获取指定序号的点位数据
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>点位数据，失败则点位数据中的序号为-1</returns>
    virtual MJPosItem GetPoint(const std::vector<MJPosItem> &points, int index) = 0;
    /**
     * @brief 查询标签名是否已经存在
     * @param labelName 输入，标签名
     * @return true-存在，false-不存在
     */
    virtual bool isLabelExisted(const std::string &label) = 0;
    /**
     * @brief 获取标签名集合
     */
    virtual std::set<std::string> getLabels() = 0;
    /**
     * @brief 添加标签名至缓存中
     * @param label 输入，标签名
     */
    virtual void addLabel(const std::string &label) = 0;
    /**
     * @brief 替换缓存中已经存在的标签名
     * @param oldLabel 输入，待替换的旧标签名
     * @param newLabel 输入，将要替换成的新标签名
     */
    virtual void replaceLabel(const std::string &oldLabel, const std::string &newLabel) = 0;
    /**
     * @brief 从缓存中删除指定的标签名
     * @param label 输入，标签名
     */
    virtual void delLabel(const std::string &label) = 0;
    /**
     * @brief 清空标签缓存
     */
    virtual void clearLabels() = 0;
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
    /// <param name="index">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    virtual int FindPoint(const std::string &fileName, int index) = 0;
    /// <summary>
    /// 查找指定序号的点位
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>存在返回点位在点位集合中的下标，不存在则返回-1</returns>
    virtual int FindPoint(const std::vector<MJPosItem> &points, int index) = 0;
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
    /// <summary>
    /// 删除点位
    /// </summary>
    /// <param name="points">输入，点位集合</param>
    /// <param name="index">输入，点位序号</param>
    /// <returns>成功返回0，其他请见错误码</returns>
    virtual int DelPoint(std::vector<MJPosItem> &points, int index) = 0;
};
