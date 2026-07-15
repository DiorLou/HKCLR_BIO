#pragma once

/*!
 * \note 根据控软平台上下层分离方案，每个路径也就是每个分区读写操作存在区别。
 * 固件区：/home/ino/inosys。创建etc bin lib等目录，存放启动脚本、可执行程序、库文件。其中文件只读，不会存在写操作。
 * 配置区：/home/ino/inocfg。存放修改较少的配置文件，其中的文件数据尽量以读为主。
 * 数据区：/home/ino/inodata。存放频繁读写和功能生成过程文件以及log记录文件。
 * tmp区: /tmp。存放频繁读写和功能生成的过程文件。该分区映射到内存，掉电不保存。
 *
 * \note 对于PC端，所有文件都是相对于应用执行路径创建。
 *
 * \note 所有路径前缀结尾都包含了分隔符。
 */

#if defined PLATFORM_COBOT_TP_MINGW_WIN
    #define MINGW_PATH_PREFIX   std::string("../share/studio")
    #define SYS_PATH_PREFIX     std::string("./")
    #define SYS_ETC_PATH_PREFIX std::string("./")
    #define SYS_BIN_PATH_PREFIX (MINGW_PATH_PREFIX + "/")
    #define SYS_LIB_PATH_PREFIX std::string("./")
    #define CFG_PATH_PREFIX     (MINGW_PATH_PREFIX + "/config/")
    #define DATA_PATH_PREFIX    (MINGW_PATH_PREFIX + "/")
    #define TMP_PATH_PREFIX     (MINGW_PATH_PREFIX + "/")
    #define STATIC_CFG_PATH     (MINGW_PATH_PREFIX + "/static_config/")
    #define PLUGIN_PATH         std::string("./plugin/")
#elif defined PLATFORM_COBOT_TP_ANDROID_X86_64 || defined PLATFORM_COBOT_TP_ANDROID_ARM_V7A || defined PLATFORM_COBOT_TP_ANDROID_ARM_64_V8A  || defined PLATFORM_COBOT_TP_ANDROID_X86
    #define ANDROID_PATH_PREFIX std::string("/storage/emulated/0/Android/data/org.qtproject.InoCobotTP/files/share/studio")
    #define SYS_PATH_PREFIX     std::string("./")
    #define SYS_ETC_PATH_PREFIX std::string("./")
    #define SYS_BIN_PATH_PREFIX ANDROID_PATH_PREFIX + "/"
    #define SYS_LIB_PATH_PREFIX std::string("./")
    #define CFG_PATH_PREFIX     (ANDROID_PATH_PREFIX + "/config/")
    #define DATA_PATH_PREFIX    (ANDROID_PATH_PREFIX + "/")
    #define TMP_PATH_PREFIX     (ANDROID_PATH_PREFIX + "/")
    #define STATIC_CFG_PATH     (ANDROID_PATH_PREFIX + "/static_config/")
    #define PLUGIN_PATH         std::string("./plugin/")
#elif defined(__linux__)
    #define SYS_PATH_PREFIX     std::string("/home/ino/inosys/")
    #define SYS_ETC_PATH_PREFIX std::string("/home/ino/inosys/etc/")
    #define SYS_BIN_PATH_PREFIX std::string("/home/ino/inosys/bin/")
    #define SYS_LIB_PATH_PREFIX std::string("/home/ino/inosys/lib/")
    #define CFG_PATH_PREFIX     std::string("/home/ino/inocfg/")
    #define DATA_PATH_PREFIX    std::string("/home/ino/inodata/")
    #define TMP_PATH_PREFIX     std::string("/tmp/")
    #define STATIC_CFG_PATH     std::string("/home/ino/inosys/static_config/")
    #define PLUGIN_PATH         std::string("/home/ino/inosys/plugin/")
#else
    #define SYS_PATH_PREFIX     std::string("./")
    #define SYS_ETC_PATH_PREFIX std::string("./")
    #define SYS_BIN_PATH_PREFIX std::string("./")
    #define SYS_LIB_PATH_PREFIX std::string("./")
    #define CFG_PATH_PREFIX     std::string("./config/")
    #define DATA_PATH_PREFIX    std::string("./")
    #define TMP_PATH_PREFIX     std::string("./")
    #define STATIC_CFG_PATH     std::string("./static_config/")
    #define PLUGIN_PATH         std::string("./plugin/")
#endif
