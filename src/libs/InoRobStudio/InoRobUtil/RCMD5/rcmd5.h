#pragma once

#include "dllspec.h"
// #include "IInoRobUtil.h"
// #include <stdint.h>
#define SHA256_SUM_LEN	32
#define MD5_SUM_LEN	16


namespace InoRobUtil {

typedef struct{
    unsigned int total[2];
    unsigned int state[8];
    unsigned char buffer[64];
}sha256_context;


struct MD5Context {
    unsigned int buf[4];
    unsigned int bits[2];
    unsigned char in[64];
};

//这里的计算MD5是从控制器代码移植过来的
//与控制器的MD5计算结果一致
class INOROBUTIL_CLASS RCMD5
{

public:
    static int ino_md5_file(const char* path, unsigned char digest[16]);
    static void ino_md5_v2c(unsigned char digest[16], char mdc[32]);
};

}




