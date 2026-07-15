/***************************************************************************
 * File Descrip : 多语言翻译接口
 ***************************************************************************/
#ifndef LANGUAGESERVICE_H
#define LANGUAGESERVICE_H
#include <iostream>
#include <string>

/**
 * @brief 翻译函数
 * @param 键值
 * @return 翻译后的内容
 */

std::string MTR(const std::string &entryCode);

#endif  // LANGUAGESERVICE_H
