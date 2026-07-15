#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "udf.h"
namespace ftp
{
class client;
}

class UDF;

class UDFPrivate
{

public:
    using String = std::string;
    using StringList = std::vector<std::string>;

    bool connect();

    void disConnect();
    //目录是否存在
    bool isDirExisted(const String &remoteDir);

    //创建目录
    bool mdir(const String &remotePath);

    //文件是否存在
    bool isFileExisted(const String &remotePath);

    //获取指定目录下文件的路径 不递归
    bool fileList(const String &remoteDir, StringList &ans);

    //获取指定目录下文件名称 不递归
    bool directoryList(const String &remoteDir, StringList &ans);

    //获取指定目录下文件的路径或者名称 不递归
    bool getRemoteDirectoryAndFileList(const String &remoteDir,  StringList &ans);

    //获取指定目录下所有文件的名 递归
    bool recursionFileList(const String &remoteDir, std::vector<std::string> &ans);

    //下载文件
    bool downloadFile(const String &remotePath, const String &localPath);

    //下载文件列表
    bool downloadFiles(const StringList &remotePath, const StringList &localPath, const UDF::TranferCallBack &callBack, void *customData);

    //下载文件夹 所有文件层级结构
    bool downloadDirectory(const String &remoteDir, const String &localDir, const UDF::TranferCallBack &callBack, void *customData);

    //上传文件
    bool uploadFile(const String &remotePath, const String &localPath);

    //上传文件列表
    bool uploadFiles(const StringList &remotePath, const StringList &localPath, const UDF::TranferCallBack &callBack, void *customData);

    //上传文件夹
    bool uploadDir(const String &remotePath, const String &localPath, bool deleteRemoteDirBeforeRemove, const UDF::TranferCallBack &callBack, void *customData);

    //删除文件夹 递归删除
    bool removeDir(const String &remoteDir, int &currentFileCount, const UDF::TranferCallBack &callBack, void *customData);

    //删除文件
    bool removeFile(const String &remoteFileName);

    //删除文件列表
    bool removeFiles(const StringList &remoteFilePathList, const UDF::TranferCallBack &callBack, void *customData);

    // /**
    //  * @brief 获取远端目录的大小(单位:bytes，会遍历目录和子目录的所有文件)
    //  * @param remoteDir 输入，远端目录
    //  */
    // uint64_t getDirSize(const std::string &remoteDir);
public:
    UDFPrivate(UDF *);
    ~UDFPrivate();
    void addErrorMsg(const String &error, std::initializer_list<const String> args = std::initializer_list<const String>());
    ftp::client *communication;
    friend class UDF;
    UDF *m_publicData;

    bool m_isLogError = true;

    String m_ip;
    int m_port;
    String m_userName;
    String m_password;

    StringList m_errorStrList;

    bool splitNameFromRemoteMetaData(String src, String &dest);
    bool getRemoteDirectoryAndFileListMetaData(const String &remoteDir, StringList &ans);
    bool getRemoteDirectoryAndFileList(const String &remoteDir, StringList &ans, int mode);

    bool getLocalDirectoryIsExist(const String &folderPath);
    bool getLocalFileIsExist(const String &filePath);
    String getLocalDirectoryFromFileName(const String &folderPath);
    bool getLocalFileList(const String &localPath, StringList &files, int &count);
    bool listFilesInDirectory(const String &localPath, StringList &files);

    bool createLocalDirectory(const String &folderPath);

};
