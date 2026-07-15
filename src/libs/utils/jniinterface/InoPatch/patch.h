#ifndef PATCH_H
#define PATCH_H

#if defined(__ANDROID__)

#include "bzip2/bzlib.h"

bool patch(const char *oldPath, const char *newPath, const char *patchPath);

#endif

#endif
