//
// Created by oceanstar on 2021/8/13.
//
#include "dllspec.h"

#ifndef OCEANSTAR_HTTP_ACL_BASE64_H
#define OCEANSTAR_HTTP_ACL_BASE64_H

// namespace oceanstar {
    /**
     * BASE64 编码函数
     * @param in {const char*} 源数据
     * @param len {int} 源数据的长度
     * @return unsigned char * 返回值需要手动free释放
     */
    unsigned char* acl_base64_encode(const char* in, int len);


    /**
     * BASE64 解码函数
     * @param in {const char*} 编码数据
     * @param len {int} 数据长度
     * @return unsigned char * NULL: 解码失败; !=NULL: 解码成功，需要free释放
     */
    unsigned char* acl_base64_decode(const char* in, int len);
    
    /**
     * 综合加密函数
     * @param strSource 原始数组
     * @param strSourceLen 原始数组长度
     * @param strKey 秘钥数组
     * @param keyLen 秘钥数组长度
     * @return 加密之后的数组（需要手动释放）
     */
extern char* INOROBUTIL_CLASS encryption(char* strSource, int strSourceLen, char* strKey, int keyLen);

    /**
     * 综合解密函数
     * @param strSource 待解密数组
     * @param strSourceLen 待解密数组长度
     * @param strKey 秘钥数组
     * @param keyLen 秘钥长度
     * @return 解密之后数组（需要手动释放）
     */
extern char* INOROBUTIL_CLASS Decrypt(char* strSource,int strSourceLen, char* strKey, int keyLen);
// }
#endif //OCEANSTAR_HTTP_ACL_BASE64_H

