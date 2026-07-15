#ifndef DIFF_H
#define DIFF_H

#if defined(__ANDROID__)
#include "bzip2/bzlib.h"

bool diff(const char *oldPath, const char *newPath, const char *patchPath);

#endif

#endif
