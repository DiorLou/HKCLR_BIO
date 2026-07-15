// 容器类，用于管理DLL中导出的单例对象。（保证在dll模块申请的内存由dll释放）

#pragma once
#include "Singleton.h"

#undef GetObject

template <class T>
class CContainer
{
public:
    CContainer(void)
    {
        m_pObject = CSingleton<T>::Instance(false);
    }

    virtual ~CContainer(void)
    {
        Clear();
    }

    void Clear(void)
    {
        if (m_pObject != NULL)
        {
            delete m_pObject;
            m_pObject = NULL;
        }
    }

    T *GetObject(void)
    {
        return m_pObject;
    }

    T *GetObj(void)
    {
        return m_pObject;
    }

    // 禁止调用拷贝构造函数和赋值函数
protected:
    CContainer(const CContainer &other);
    CContainer &operator=(const CContainer &other);

private:
    T *m_pObject;
};
