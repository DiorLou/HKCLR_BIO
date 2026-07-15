#pragma once
#include "dllspec.h"
#include "IInoRobBusiness.h"

namespace InoRobBusinessProxy
{
class INOROBBUSINESSPROXY_CLASS DataSrvBase_V1
{
#pragma region 构造与析构

private:
    IDataSrvBase *_dataSrvBase = nullptr;

public:
    DataSrvBase_V1(IDataSrvBase *dataSrvBase);
    ~DataSrvBase_V1();

#pragma endregion

#pragma region 业务逻辑

public:
    // 插件WRITE文本
    // request 请求内容（注：长度不超过 864 * 32 - 1）
    int PluginTextWrite(const string &request);
    // 插件READ文本
    // request 请求内容（注：仅支持ASCII，长度不超过 864 - 1）
    // response 响应内容（注：仅支持ASCII，长度不超过 864 * 32 - 1）
    int PluginTextRead(const string &request, string &response);

    // 插件WRITE二进制
    // name 结构体名称（仅支持ASCII，长度不超过 24 - 1）
    // request 请求内容，不能为空，需要将结构体转换为字节流，长度不超过 840 * 32）
    //         注1：结构体中不能包含不定长成员，比如string成员，指针等
    //         注2：结构体使用4字节对齐
    int PluginBinaryWrite(const string &name, vector<char> &request);
    // 插件READ二进制
    // name 结构体名称（注：仅支持ASCII，长度不超过24 - 1）
    // responseLength 指定接收数据的长度（提供结构体的字节大小，通信按该大小分帧读取数据，不大于 840 * 32）
    // response 响应内容（注：结构体中不能包含不定长成员，比如string成员，指针等）
    int PluginBinaryRead(const string &name, int responseLength, vector<char> &response);

#pragma endregion
};
}  // namespace InoRobBusinessProxy
