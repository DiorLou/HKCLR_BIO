#pragma once
#include <string>

#ifdef _WIN32
#if defined(ZIPAPI_EXPORT)
#define ZIPAPI __declspec(dllexport)
#else
#define ZIPAPI __declspec(dllimport)
#endif
#else
#define ZIPAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

ZIPAPI int unzip(const char *zipFile, const char *outputDir, const std::string &password = "");

#ifdef __cplusplus
}
#endif
