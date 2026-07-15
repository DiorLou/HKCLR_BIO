#pragma once

#include "inorobudf_global.h"
#include <string>
#include <vector>
#include <functional>

using namespace std;
class INOROBUDF_CLASS UDF
{
public:
    using TranslteCallback = std::function<std::string(const std::string &message)>;
    using LogCallback = std::function<void(const std::string &)>;
    using TranferCallBack = std::function<void(int, int, void *)>;
    using PasswordCallBack = std::function<void(string &, int &, string &, string &)>;
    using TranslateCallBack = std::function<std::string(const string &)>;

    // 第三方开发人员可以注册其自己的日志系统 可以注册多个, 重复的仅一个生效(注册重复返回值 false) 第三方注册入口应当在InoRobotBussinss统一提供
    // 注册后应当保证在remove前或程序关闭前保持地址有效（可以销毁logCallBack，但不要销毁bind源），否则可能引起程序崩溃
    static bool registerErrorMsgCallBack(const LogCallback &callBack);

    // 移除 callBack 对应地址对应的日志回调 true成功移除 false没有找到特定函数地址对象
    static bool removeErrorMsgCallBack(const LogCallback &callBack);

    // 移除所有日志回调
    static void removeAllErrorMsgCallBack();

    // // 翻译回调函数只能注册一次，由InoRobotBussiness注册, 非第一次注册返回false
    // static bool registerErrorMsgCallBack(const TranslteCallback &callback);

    // 注册FTP登录所需信息的回调函数 callback回调 name名称
    template <class T>
    static PasswordCallBack bindPassword(T *address, void (T::*fun)(string &, int &, string &, string &))
    {
        return std::bind(fun, address, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
    }
    // PasswordCallBack四个参数分别表示 ip port username password
    // 返回值为注册的回调索引，可以使用索引初始化UDF类,若已注册过相同地址，返回值为已有索引
    static int registerPassWordCallBack(const PasswordCallBack &callback, const string &name);

    static int modifyPassWordCallBack(const PasswordCallBack &callback, const string &oldName, const string &newName);

    //注册翻译函数回调
    static bool registerTranslateCallBack(const TranslateCallBack &callBack);
    // 移除特定索引的回调，需要索引和函数地址均正确才可成功移除
    //  原索引1 2 3 4，移除2后为1 3 4，索引保持不变
    static bool removePassWordCallBack(const string &name, const PasswordCallBack &callback);

    // 传输进度《同步》回调函数,请不要在回调中阻塞线程，也不要在传输途中销毁bind源（比如销毁类实例），请注意线程安全
    // 调用时机：传输/删除第N个文件之后，第N+1个文件之前
    // 第一个参数总共多少个文件，第二个参数当前已经传输/删除了几个文件, 第三个参数用户自定义数据，会原封不动传递给回调函数
    // 递归删除文件夹第一个参数永远为-1，第二个参数为已删除多少个文件
    // 示例：
    // UDF udf();
    // udf.downloadDirectory("remote", "loacl" , UDF::bind(this, &RobotDebug::tranferFileProcess));
    // this 为类RobotDebug实例地址
    // RobotDebug::tranferFileProcess为类成员函数，即void RobotDebug::tranferFileProcess(unsigned int, unsigned int)
    // 也可使用如下模板 需要将成员函数设置为公有，否则需要自己手动绑定
    // 手动绑定示例：
    // UDF::TranferCallBack callback = bind(&RobotDebug::tranferFileProcess, this, placeholders::_1, placeholders::_2);
    // udf.downloadDirectory("remote", "local" , callback);
    // 也可以手动绑定一个匿名函数
    template <class T>
    static TranferCallBack bindTransfer(T *address, void (T::*fun)(int, int, void *))
    {
        return std::bind(fun, address, placeholders::_1, placeholders::_2, placeholders::_3);
    }
#define EMPTY_CALLBACK TranferCallBack()

    // 使用回调函数列表对应索引的回调获取ftp连接所需信息
    UDF(const int index = 0, const bool printLog = true);
    UDF(const string &name, const bool printLog = true);
    UDF(const string &ip, const int port, const string &userName, const string &passwrod, bool printLog = true);
    ~UDF();

    bool isPrintErrorLog();
    void setPrintErrorLog(bool isPrintErrorLog);
    // 用户可以通过该接口将错误信息广播到多个日志系统 注意：该接口不裹挟翻译
    // 后续去除该接口，统一接口由InoRobotBussiness提供
    void logErrorMsg(const string &errorMsg);

    // 创建目录
    bool makedir(const string &remotePath);

    // 目录是否存在
    bool isDirExisted(const string &remoteDir);

    // 文件是否存在
    bool isFileExisted(const string &remotePath);

    // 获取指定目录下文件的路径 不递归
    bool fileList(const string &remoteDir, vector<string> &ans);

    // 获取指定目录下文件名称 不递归
    bool directoryList(const string &remoteDir, vector<string> &ans);

    // 获取指定目录下文件的路径或者名称 不递归
    bool getRemoteDirectoryAndFileList(const string &remoteDir, vector<string> &ans);

    // 获取指定目录下所有文件的名 递归
    bool recursionFileList(const string &remoteDir, vector<string> &ans);

    // 下载文件 localPath需要携带文件名称
    bool downloadFile(const string &remotePath, const string &localPath);

    // 下载文件集 callBack回调函数用于获取当前进度，下同
    bool downloadFiles(const vector<string> &remotePath, const vector<string> &localPath, const TranferCallBack &callBack = EMPTY_CALLBACK, void *customData = 0);

    // 下载文件夹 递归
    bool downloadDirectory(const string &remoteDir, const string &localDir, const TranferCallBack &callBack = EMPTY_CALLBACK, void *customData = 0);

    // 上传文件 remotePath需要携带文件名称
    bool uploadFile(const string &remotePath, const string &localPath);

    // 上传文件
    bool uploadFiles(const string &remotePath, const string &localPath);

    // 上传文件夹
    bool uploadDir(const string &remotePath, const string &localPath, bool deleteRemoteDirBeforeRemove, const TranferCallBack &callBack = EMPTY_CALLBACK, void *customData = 0);

    // 删除文件
    bool removeFile(const string &remoteFileName);

    // 删除文件列表
    bool removeFiles(const vector<string> &remoteFilePathList, const TranferCallBack &callBack = EMPTY_CALLBACK, void *customData = 0);

    // 删除文件夹 递归删除
    bool removeDir(const string &remoteDir, const TranferCallBack &callBack = EMPTY_CALLBACK, void *customData = 0);

    string getLastErrorStr();
private:
    void *m_privateData;
};
