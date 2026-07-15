#pragma once
#include <vector>
#include "IUtil.h"
#include <string>
namespace InoRobUtil
{
/**********************************************************
 * FTP客户端抽象，在业务模型层中使用FTP时，应依赖注入该抽象。
 * 1、否则业务模型层的方法无法进行单元测试
 * 2、当更换其它FTP实现时，业务模型层无需变更代码，符合开闭原则
 * Update by WuJian at 2024/6/21 FTP客户端抽象规范
 ***********************************************************/
class INOROBUTIL_CLASS IFtp
{
public:
    virtual ~IFtp() {}
    
    /**
     * @brief 当前目录 (如果失败了，则返回空字符串)
    */
    virtual std::string currentDir() = 0;

    /**
     * @brief 获取当前目录中所有文件的路径或名称 (如果失败了，则返回空集合)
     * @param isOnlyNames 输入，true-返回文件名称集合，false-返回文件路径集合
    */
    virtual std::vector<std::string> currentFileList(bool isOnlyNames = false) = 0;

    /**
     * @brief 获取指定目录下所有文件的路径或者名称 (如果失败了，则返回空集合)
     * @param remotDir 输入，远端目录
     * @param isOnlyNames 输入，true-返回文件名称集合，false-返回文件路径集合
    */
    virtual std::vector<std::string> fileList(const std::string &remotDir, bool isOnlyNames = false) = 0;

    /**
     * @brief 进入指定目录
     * @param remotDir 输入，远端目录
     * @return 成功返回0，其他请见错误码
    */
    virtual int cd(const std::string &remotDir) = 0;

    /**
     * @brief 返回上一级目录
     * @return 成功返回0，其他请见错误码
    */
    virtual int cdUp() = 0;

    /**
     * @brief 创建目录
     * @param remotDir 输入，远端目录
     * @return 成功返回0，其他请见错误码
    */
    virtual int mkDir(const std::string &remotDir) = 0;

    /**
     * @brief 删除目录
     * @param remotDir 输入，远端目录
     * @return 成功返回0，其他请见错误码
    */
    virtual int rdDir(const std::string &remotDir) = 0;

    /**
     * @brief 删除文件
     * @param remotePath 输入，远端路径
     * @return 成功返回0，其他请见错误码
    */
    virtual int removeFile(const std::string &remotePath) = 0;

    /**
     * @brief 重命名文件
     * @param oldFilePath 输入，旧远端路径
     * @param newFilePath 输入，新远端路径
     * @return 成功返回0，其他请见错误码
    */
    virtual int renameFile(const std::string &oldFilePath, const std::string &newFilePath) = 0;

    /**
     * @brief 获取远端文件的大小(单位:bytes)
     * @param remotePath 输入，远端路径
    */
    virtual uint64_t getFileSize(const std::string &remotePath) = 0;

    /**
     * @brief 获取远端目录的大小(单位:bytes，会遍历目录和子目录的所有文件)
     * @param remoteDir 输入，远端目录
    */
    virtual uint64_t getDirSize(const std::string &remoteDir) = 0;

    /**
     * @brief 目录是否存在
     * @param remotDir 输入，远端目录
     * @return true-存在，false-不存在
    */
    virtual bool isDirExisted(const std::string &remotDir) = 0;

    /**
     * @brief 文件是否存在
     * @param remotePath 输入，远端路径
     * @return true-存在，false-不存在
    */
    virtual bool isFileExisted(const std::string &remotePath) = 0;

    /**
     * @brief 下载文件
     * @param remotePath 输入，远端路径
     * @param localPath 输入，本地路径
     * @return 成功返回0，其他请见错误码
    */
    virtual int downloadFile(const std::string &remotePath, const std::string &localPath) = 0;

    /**
     * @brief 上传文件
     * @param remotePath 输入，远端路径
     * @param localPath 输入，本地路径
     * @return 成功返回0，其他请见错误码
    */
    virtual int uploadFile(const std::string &remotePath, const std::string &localPath) = 0;

    /**
     * @brief 下载远端目录中的所有文件
     * @param remotDir 输入，远端目录
     * @param localDir 输入，本地目录
     * @return 成功返回0，其他请见错误码
    */
    virtual int downloadFiles(const std::string &remotDir, const std::string &localDir) = 0;

    /**
     * @brief 下载远端文件路径集合中的所有文件
     * @param remotePaths 输入，远端文件路径集合
     * @param localPaths 输入，本地文件路径集合
     * @return 成功返回0，其他请见错误码
    */
    virtual int downloadFiles(const std::vector<std::string> &remotePaths, const std::vector<std::string> &localPaths) = 0;

    /**
     * @brief 上传本地目录中的所有文件
     * @param remotDir 输入，远端目录
     * @param localDir 输入，本地目录
     * @return 成功返回0，其他请见错误码
    */
    virtual int uploadFiles(const std::string &remotDir, const std::string &localDir) = 0;

    /**
     * @brief 上传远端文件路径集合中的所有文件
     * @param remotePaths 输入，远端文件路径集合
     * @param localPaths 输入，本地文件路径集合
     * @return 成功返回0，其他请见错误码
    */
    virtual int uploadFiles(const std::vector<std::string> &remotePaths, const std::vector<std::string> &localPaths) = 0;

};

};  // namespace InoRobUtil
