#pragma once


#ifdef _WIN32
    #ifdef INOROBUDF_EXPORTS
        #define INOROBUDF_CLASS __declspec(dllexport)
    #else
        #define INOROBUDF_CLASS __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define INOROBUDF_CLASS
#else
    #define INOROBUDF_CLASS
#endif
