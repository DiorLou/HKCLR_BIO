#pragma once

#include "generaltools_global.h"
#include <vector>

GENERALTOOLS_EXPORT bool getUSBStickDeveics(char *devices, int size);
GENERALTOOLS_EXPORT int umountUSBStick(const char *point);
GENERALTOOLS_EXPORT bool shellExectue(const char *cmd);

GENERALTOOLS_EXPORT bool fileIsExist(const char *filePath);

GENERALTOOLS_EXPORT void makeFilePath(
    const char *dirName, const char *fileName,
    std::string &filePath);

GENERALTOOLS_EXPORT bool getUSBDeveics(std::vector<std::string> &devices);
