#pragma once
#include "DataSrvGlobal.h"

namespace InoRobUtil
{
class INOROBUTIL_CLASS JsonSerInterferenceZone
{
public:
    static cJSON *ToJson_INTERFER_ZONE_STATUS(INTERFER_ZONE_STATUS *data);
    static bool FromJson_INTERFER_ZONE_STATUS(cJSON *obj, INTERFER_ZONE_STATUS *data);

    static cJSON *ToJson_INTERFER_ZONE(INTERFER_ZONE *data);
    static bool FromJson_INTERFER_ZONE(cJSON *obj, INTERFER_ZONE *data);

    static cJSON *ToJson_INTERFER_ZONE_WOBJPARAM(INTERFER_ZONE_WOBJPARAM *data);
    static bool FromJson_INTERFER_ZONE_WOBJPARAM(cJSON *obj, INTERFER_ZONE_WOBJPARAM *data);

    static cJSON *ToJson_INTERFER_MTCP_BOX(INTERFER_MTCP_BOX *data);
    static bool FromJson_INTERFER_MTCP_BOX(cJSON *obj, INTERFER_MTCP_BOX *data);

    static cJSON *ToJson_INTERFER_BALL_BOX(INTERFER_BALL_BOX *data);
    static bool FromJson_INTERFER_BALL_BOX(cJSON *obj, INTERFER_BALL_BOX *data);

    static cJSON *ToJson_INTERFER_TOOL_BOX(INTERFER_TOOL_BOX *data);
    static bool FromJson_INTERFER_TOOL_BOX(cJSON *obj, INTERFER_TOOL_BOX *data);

    static cJSON *ToJson_INTERFER_TOOL(INTERFER_TOOL *data);
    static bool FromJson_INTERFER_TOOL(cJSON *obj, INTERFER_TOOL *data);

    static cJSON *ToJson_INTERFER_ZONE_MTCPTOOLPARAM(INTERFER_ZONE_MTCPTOOLPARAM *data);
    static bool FromJson_INTERFER_ZONE_MTCPTOOLPARAM(cJSON *obj, INTERFER_ZONE_MTCPTOOLPARAM *data);
};
}  // namespace InoRobUtil
