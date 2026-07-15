#pragma once
#include "OSUpdateToolLib.h"
class UpdateCommon
{
public:
	UpdateCommon();
	~UpdateCommon();
	int UnzipFirmwareInBoard_SSH(UpdateCfg cfg);
	int CheckDirStatus_SSH(UpdateCfg cfg);
private:

};

