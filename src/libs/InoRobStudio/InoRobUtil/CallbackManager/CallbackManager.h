#ifndef CALLBACKMANAGER_H
#define CALLBACKMANAGER_H
#include <functional>
#include <string>
#include "dllspec.h"

std::string UTILMTR(const std::string &in);

class INOROBUTIL_CLASS CallbackManager {

public:
    using TranslateCallBack = std::function<std::string(const std::string &message)>;

    //注册翻译函数回调
    static bool RegisterTranslateCallBack(const TranslateCallBack &callBack);
};

#endif  // CALLBACKMANAGER_H
