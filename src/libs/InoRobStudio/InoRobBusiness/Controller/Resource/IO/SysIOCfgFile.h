#pragma once
#include "../IResource.h"

namespace InoRobBusiness
{
class SysIOCfgFile
{
public:
    /**
     * @brief 从系统IO配置文件中读取配置数据
     * @param[out] sysIODats 读取到的系统IODats
     * @return 0成功 其他请见错误码
     */
    static int fromFile(std::array<SysIODat, CABINET_COUNT> &sysIODats);
};
}  // namespace InoRobBusiness
