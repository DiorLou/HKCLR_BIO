#pragma once
#include <string.h>

namespace InoRobBusiness
{
/*
    Grpc服务
    Create by WuJian at 2024/10/17
*/
class IGrpcService
{
public:
    virtual ~IGrpcService()
    {
    }
    // 启动Grpc服务
    virtual bool Start(std::string appRootPath) = 0;
};
}  // namespace InoRobBusiness
