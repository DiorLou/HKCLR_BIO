#pragma once
#include "IInoRobUtil.h"


namespace InoRobUtil
{
/**
 * @brief 虚拟控制器FTP二次封装类
 * 虚拟控制器使用模拟的FTP服务, 通过文件操作实现
 */
class INOROBUTIL_CLASS FileCast : IFtp
{
public:
    FileCast();
    ~FileCast();

public:
    /**
     * @brief 当前目录 (如果失败了，则返回空字符串)
     */
    virtual std::string currentDir() override;

    /**
     * @brief 获取当前目录中所有文件的路径或名称 (如果失败了，则返回空集合)
     * @param isOnlyNames 输入，true-返回文件名称集合，false-返回文件路径集合
     */
    virtual std::vector<std::string> currentFileList(bool isOnlyNames = false) override;

    /**
     * @brief 获取指定目录下所有文件的路径或者名称 (如果失败了，则返回空集合)
     * @param remotDir 输入，远端目录
     * @param isOnlyNames 输入，true-返回文件名称集合，false-返回文件路径集合
     */
    virtual std::vector<std::string> fileList(const std::string &remoteDir, bool isOnlyNames = false) override;

    /**
     * @brief 进入指定目录
     * @param remotDir 输入，远端目录
     * @return 成功返回0，其他请见错误码
     */
    virtual int cd(const std::string &remoteDir) override;

    /**
     * @brief 返回上一级目录
     * @return 成功返回0，其他请见错误码
     */
    virtual int cdUp() override;

    /**
     * @brief 创建目录
     * @param remotDir 输入，远端目录
     * @return 成功返回0，其他请见错误码
     */
    virtual int mkDir(const std::string &remoteDir) override;

    /**
     * @brief 删除目录
     * @param remotDir 输入，远端目录
     * @return 成功返回0，其他请见错误码
     */
    virtual int rdDir(const std::string &remoteDir) override;

    /**
     * @brief 删除文件
     * @param remotePath 输入，远端路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int removeFile(const std::string &remotePath) override;

    /**
     * @brief 重命名文件
     * @param oldFilePath 输入，旧远端路径
     * @param newFilePath 输入，新远端路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int renameFile(const std::string &oldFilePath, const std::string &newFilePath) override;

    /**
     * @brief 获取远端文件的大小(单位:bytes)
     * @param remotePath 输入，远端路径
     */
    virtual uint64_t getFileSize(const std::string &remotePath) override;

    /**
     * @brief 获取远端目录的大小(单位:bytes，会遍历目录和子目录的所有文件)
     * @param remoteDir 输入，远端目录
     */
    virtual uint64_t getDirSize(const std::string &remoteDir) override;

    /**
     * @brief 目录是否存在
     * @param remotDir 输入，远端目录
     * @return true-存在，false-不存在
     */
    virtual bool isDirExisted(const std::string &remoteDir) override;

    /**
     * @brief 文件是否存在
     * @param remotePath 输入，远端路径
     * @return true-存在，false-不存在
     */
    virtual bool isFileExisted(const std::string &remotePath) override;

    /**
     * @brief 下载文件
     * @param remotePath 输入，远端路径
     * @param localPath 输入，本地路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int downloadFile(const std::string &remotePath, const std::string &localPath) override;

    /**
     * @brief 上传文件
     * @param remotePath 输入，远端路径
     * @param localPath 输入，本地路径
     * @return 成功返回0，其他请见错误码
     */
    virtual int uploadFile(const std::string &remotePath, const std::string &localPath) override;

    /**
     * @brief 下载远端目录中的所有文件
     * @param remotDir 输入，远端目录
     * @param localDir 输入，本地目录
     * @return 成功返回0，其他请见错误码
     */
    virtual int downloadFiles(const std::string &remoteDir, const std::string &localDir) override;

    /**
     * @brief 下载远端文件路径集合中的所有文件
     * @param remotePaths 输入，远端文件路径集合
     * @param localPaths 输入，本地文件路径集合
     * @return 成功返回0，其他请见错误码
     */
    virtual int downloadFiles(const std::vector<std::string> &remotePaths, const std::vector<std::string> &localPaths) override;

    /**
     * @brief 上传本地目录中的所有文件
     * @param remotDir 输入，远端目录
     * @param localDir 输入，本地目录
     * @return 成功返回0，其他请见错误码
     */
    virtual int uploadFiles(const std::string &remotDir, const std::string &localDir) override;

    /**
     * @brief 上传远端文件路径集合中的所有文件
     * @param remotePaths 输入，远端文件路径集合
     * @param localPaths 输入，本地文件路径集合
     * @return 成功返回0，其他请见错误码
     */
    virtual int uploadFiles(const std::vector<std::string> &remotePaths, const std::vector<std::string> &localPaths) override;

public:
    // 重置路径
    bool restoreOriginalLocation(const std::string &route);

    // 获取当前路径
    bool getCurrentLocation(std::string &retRoute);

    /**
     * @brief 获取虚拟控制器FTP原始位置
     * @return
     */
    std::string getFTPOriginalLocation();

    /**
     * @brief 获取虚拟控制器FTP根路径
     * @return
     */
    std::string getFTPRootLocation();

private:
    bool checkRoute();

private:
    static std::string _rootLocation;      // 虚拟控制器根路径, 绝对路径
    static std::string _originalLocation;  // FTP初始路径, 绝对路径
    static std::string _currentLocation;   // 模拟当前工作路径, 绝对路径
};
}  // namespace InoRobUtil
