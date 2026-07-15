#pragma once
#include "dllspec.h"
#include <string>
#include "../Include/ICommonData.h"
#include "instruction/CmdForInoRobotLab.h"

namespace InoRobBusinessProxy
{
/// <summary>
/// 公共数据
/// </summary>
class INOROBBUSINESSPROXY_CLASS CommonDataConvert
{
public:
#if (defined INOROBBUSINESSPROXY_EXPORTS) || (defined PLUGIN_EXPORTS)
    static void SystemActionScopInstListToSystemActionScopInstListAgent(const SystemActionScopInstList &InstList, SystemActionScopInstListAgent &InstListAgent);
    static SystemSpecialInstListAgent *SystemSpecialInstListToSystemSpecialInstListAgent(SystemSpecialInstList *pstSpecialInstList);

    static void SystemActionScopInstListAgentToSystemActionScopInstList(const SystemActionScopInstListAgent &InstListAgent, SystemActionScopInstList &InstList);
    static SystemSpecialInstList *SystemSpecialInstListAgentToSystemSpecialInstList(SystemSpecialInstListAgent *pstSpecialInstListAgent);

    static void SystemSpecialInstListToSystemSpecialInstListAgent(const SystemSpecialInstList &pstSpecialInstList, SystemSpecialInstListAgent &pstSpecialInstListAgent);
#endif
};
}  // namespace InoRobBusinessProxy