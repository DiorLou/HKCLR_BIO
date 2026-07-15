/************************************************************************
 *                        INOVANCE TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2018
 *
 * Description: ms level counter and sleep
 *
 * Functions: None.
 *
 * Modification Log:
 * Date          Name             Description Of Change
 * 2018-10-09    Bruce nie        Creation.
 ***********************************************************************/
/**************************************************************
 * class IVCSysPerfCounter
 **************************************************************/
#ifndef __SYSPERFCOUNTER_HPP__
#define __SYSPERFCOUNTER_HPP__

#include <Windows.h>

#pragma comment(lib, "winmm.lib")

class IVCSysPerfCounter
{
public:
    IVCSysPerfCounter()
    {
        if (IVCSysPerfCounter::s_nFreq.QuadPart <= 0)
            ::QueryPerformanceFrequency(&IVCSysPerfCounter::s_nFreq);

        //		gs_Log.GetObject()->Debug("\r\n[IVCSysPerfCounter] IVCSysPerfCounter::s_nFreq(%u)\r\n", IVCSysPerfCounter::s_nFreq.QuadPart);

        m_nBeginTime.QuadPart = 0;
        m_nEndTime.QuadPart = 0;
    }

    virtual ~IVCSysPerfCounter()
    {
    }

    void StartCount()
    {
        QueryPerformanceCounter(&m_nBeginTime);
    }
    double EndCount(bool bClr = true)
    {
        double dCountms;

        ::QueryPerformanceCounter(&m_nEndTime);

        dCountms = (double)(m_nEndTime.QuadPart - m_nBeginTime.QuadPart) * 1000.0 / IVCSysPerfCounter::s_nFreq.QuadPart;

        if (bClr)
        {
            m_nBeginTime.QuadPart = 0;
            m_nEndTime.QuadPart = 0;
        }

        return dCountms;
    }

    // sleep microseconds
    static void IVUSleep(__int64 i64MicroSeconds)
    {
        LARGE_INTEGER largeIntTmp;
        if (IVCSysPerfCounter::s_nFreq.QuadPart <= 0)
            ::QueryPerformanceFrequency(&IVCSysPerfCounter::s_nFreq);

        __int64 tStartTimeTick;
        ::QueryPerformanceCounter(&largeIntTmp);
        tStartTimeTick = (__int64)largeIntTmp.QuadPart;

        // free cpu time --sleep (n-1) * 100ms
        DWORD tTimeToSleep100ms = (DWORD)(i64MicroSeconds / (1000 * 100));
        if (tTimeToSleep100ms > 1)
            ::Sleep((tTimeToSleep100ms - 1) * 100);

        while (1)
        {
            __int64 tCurTimeTick;
            ::QueryPerformanceCounter(&largeIntTmp);
            tCurTimeTick = (__int64)largeIntTmp.QuadPart;

            double dTimeDelta = (double)(tCurTimeTick - tStartTimeTick);
            dTimeDelta = (dTimeDelta * 1000000.0) / IVCSysPerfCounter::s_nFreq.QuadPart;

            if (dTimeDelta >= (double)i64MicroSeconds)
                break;

            // free cpu time -- sleep 20ms
            if (((double)i64MicroSeconds - dTimeDelta) >= (1000 * 50))
            {
                ::Sleep(20);  // typical windows time slice
            }
        }

        return;
    }

public:
    static LARGE_INTEGER s_nFreq;

private:
    // LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER m_nEndTime;
};

LARGE_INTEGER IVCSysPerfCounter::s_nFreq = { 0 };

#endif