#pragma once
#include <string>
#include "dllspec.h"

namespace InoRobBusiness
{

class INOROBBUSINESS_CLASS IrSub
{
public:
    IrSub(std::string url, std::string topic);
    ~IrSub();

    bool Open();

    void RegFunc(void(*func)(std::string));

    void Close();

private:
    // 工作线程
    static void WorkThreadFunc(IrSub* pthis);
    // 嵌套字
    void* _sock = nullptr;
    // 类型及地址
    std::string _url;
    // 主题
    std::string _topic;
    // 线程工作标志
    bool _workFlag = false;
    // 函数
    void(*_func)(std::string param) = nullptr;
};

}

