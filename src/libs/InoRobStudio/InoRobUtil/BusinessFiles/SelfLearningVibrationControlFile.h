#pragma once
#include "InoRobUtil.h"
#include "DataSrvGlobal.h"

namespace InoRobUtil
{

class INOROBUTIL_CLASS SelfLearningVibrationControlFile
{
public:
    SelfLearningVibrationControlFile();
    virtual ~SelfLearningVibrationControlFile();

    /// <summary>
    /// 是否为最新版本
    /// </summary>
    /// <param name="fileVersion"></param>
    /// <returns>true为最新版本，false为不是最新版本</returns>
    bool IsNewVersion(std::string fileVersion);

    /// <summary>
    /// 是否为新格式的文件
    /// </summary>
    /// <param name="fileName">文件路径</param>
    /// <param name="isNewFile">true为新格式文件，false为旧格式文件</param>
    /// <returns>成功返回0，失败查看对应错误码</returns>
    int IsNewFormatFile(std::string fileName, bool &isNewFile);

    /// <summary>
    /// 从旧版的配置文件中获取信息
    /// </summary>
    /// <param name="fileName">文件路径</param>
    /// <param name="dataStr">自学习振动抑制数据</param>
    /// <param name="dataStr">自学习振动抑制数据大小</param>
    /// <param name="fileInfo">文件信息</param>
    /// <returns>成功返回0，失败查看对应错误码</returns>
    int FromOldFile(std::string fileName, unsigned char *&dataStr, int &dataSize, FileInfo *fileInfo);

    /// <summary>
    /// 从新版的配置文件中获取信息
    /// </summary>
    /// <param name="fileName">文件路径</param>
    /// <param name="dataStr">自学习振动抑制数据</param>
    /// <param name="dataStr">自学习振动抑制数据大小</param>
    /// <param name="fileInfo">文件信息</param>
    /// <returns>成功返回0，失败查看对应错误码</returns>
    int FromFile(std::string fileName, unsigned char *&dataStr, int &dataSize, FileInfo *fileInfo);

    /// <summary>
    /// 将数据保存成新文件
    /// </summary>
    /// <param name="fileName">保存文件路径</param>
    /// <param name="dataStr">自学习振动抑制数据</param>
    /// <param name="dataStr">自学习振动抑制数据大小</param>
    /// <param name="robotName">机器人名称</param>
    /// <param name="systemVersion">系统版本</param>
    /// <returns>成功返回0，失败查看对应错误码</returns>
    int ToFile(const std::string &fileName, const unsigned char *dataStr, const int dataSize, const std::string &robotName, const std::string &systemVersion);

    /// <summary>
    /// 文件类型
    /// </summary>
    /// <returns>类型名称</returns>
    const char *GetFileType();

private:
    std::string GetValue(std::string *pContent, const char *key);
    bool GetData(std::string fileName, long offset, unsigned char *&dataStr, int &dataSize);
    bool PushBackData(std::string fileName, unsigned char *dataStr, int dataSize);
};

}  // namespace InoRobUtil
