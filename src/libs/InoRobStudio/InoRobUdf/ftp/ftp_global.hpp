#pragma once

#ifdef __linux__
    #define FTP_CLASS __attribute__((visibility("hidden")))
#else
    #define FTP_CLASS
#endif
