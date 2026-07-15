// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

#ifdef _WIN32
    #include <sdkddkver.h>
#endif

// 添加要在此处预编译的标头
#include <string>
#include <vector>
#include <array>
#include <map>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#include <cstdio>
#include <thread>
#include <shared_mutex>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <ftp/client.hpp>
#include <QObject>
#include "DataSrvGlobal.h"
#include "DataTypeDef.h"
#include "dllspec.h"
#include "signal_slot.h"
#include "InoRobLog.h"
#include "PrintInfo.h"
#include "IInoRobUtil.h"
#include "IInoRobBusiness.h"

#endif  // PCH_H
