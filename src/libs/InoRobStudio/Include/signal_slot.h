#pragma once
#include <vector>
#include <iostream>
#include <mutex>

// class IrSsMutex
// {
// public:
// 	IrSsMutex()
// 	{
// 		m_hMutex = ::CreateMutex(NULL, FALSE, NULL); //false申请时没被占用 1
// 	}
// 	~IrSsMutex()
// 	{
// 		::CloseHandle(m_hMutex);
// 	}
// 	bool Lock(int nTimeOuts = 0)
// 	{
//
// 		if (nTimeOuts == 0)
// 		{
// 			DWORD d = ::WaitForSingleObject(m_hMutex, INFINITE);
// 		}
// 		else
// 		{
// 			unsigned long  ret = ::WaitForSingleObject(m_hMutex, nTimeOuts); // 占用1
// 			return ret != WAIT_TIMEOUT;
// 		}
// 		return true;
// 	}
// 	void UnLock()
// 	{
// 		::ReleaseMutex(m_hMutex);
// 	}
// private:
// 	HANDLE m_hMutex;
// };

template <typename T1>
class slotbase
{
public:
    virtual void Execute(T1 para) = 0;
    virtual bool IsSameObj(void *obj) = 0;
};

template <typename T, typename T1>
class slotimpl : public slotbase<T1>
{
public:
    slotimpl(T *pObj, void (T::*pMemberFunc)(T1))
    {
        m_pObj = pObj;
        m_pMemberFunc = pMemberFunc;
    }
    virtual void Execute(T1 para)
    {
        (m_pObj->*m_pMemberFunc)(para);
    }
    virtual bool IsSameObj(void *pObj)
    {
        return pObj == (void *)m_pObj;
    }

private:
    T *m_pObj;
    void (T::*m_pMemberFunc)(T1);
};

template <typename T1>
class slot
{
public:
    template <typename T>
    slot(T *pObj, void (T::*pMemberFunc)(T1))
    {
        m_pSlotbase = new slotimpl<T, T1>(pObj, pMemberFunc);
    }
    ~slot()
    {
        delete m_pSlotbase;
    }
    void Execute(T1 para)
    {
        m_pSlotbase->Execute(para);
    }
    bool IsSameObj(void *pObj)
    {
        return m_pSlotbase->IsSameObj(pObj);
    }

private:
    slotbase<T1> *m_pSlotbase;
};

template <typename T1>
class rsignal
{
public:
    template <typename T>
    void bind(T *pObj, void (T::*pMemberFunc)(T1 para))
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        // 只允许同一个类只允许绑一次
        typename std::vector<slot<T1> *>::iterator ite = m_slots.begin();
        for (; ite != m_slots.end(); ite++)
        {
            if ((*ite)->IsSameObj(pObj))
            {
                return;
            }
        }
        m_slots.push_back(new slot<T1>(pObj, pMemberFunc));
    }
    ~rsignal()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        typename std::vector<slot<T1> *>::iterator ite = m_slots.begin();
        for (; ite != m_slots.end(); ite++)
        {
            delete *ite;
        }
    }
    void operator()(T1 para)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        typename std::vector<slot<T1> *>::iterator ite = m_slots.begin();
        for (; ite != m_slots.end(); ite++)
        {
            (*ite)->Execute(para);
        }
    }
    void unbind(void *pObj)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        typename std::vector<slot<T1> *>::iterator ite = m_slots.begin();
        for (; ite != m_slots.end(); ite++)
        {
            if ((*ite)->IsSameObj(pObj))
            {
                m_slots.erase(ite);
                return;
            }
        }
    }

private:
    std::vector<slot<T1> *> m_slots;
    std::mutex m_mutex;
};

#define CONNECT(sender, signal, receiver, slot) sender.signal.bind(receiver, slot)
#define DISCONNECT(sender, signal, receiver)    sender.signal.unbind(receiver)

// class receiver
//{
// public:
//	void callback1(data_u a)
//	{
//		cout << "receiver1: " << 1 << endl;
//	}
// };
// class receiver2
//{
// public:
//	void callback2(data_u a)
//	{
//		cout << "receiver2: " << 1 << endl;
//	}
// };
//
// class sender
//{
// public:
//	sender() {}
//	data_u get_value()
//	{
//		return m_value;
//	}
//	void set_value(data_u new_value)
//	{
//		m_value.data = new_value.data;
//		m_value.len = new_value.len;
//		m_valueChanged(new_value);
//	}
//	signal<data_u> m_valueChanged;
// private:
//	data_u m_value;
//
// };
//
// int main(int argc, char** arg)
//{
//	receiver r;
//	receiver2 r2;
//	sender s;
//	CONNECT(s, m_valueChanged, &r, &receiver::callback1);
//	CONNECT(s, m_valueChanged, &r2, &receiver2::callback2);
//	data_u data;
//	data.len = 100;
//	data.data = NULL;
//	s.set_value(data);
//	DISCONNECT(s, m_valueChanged, &r2);
//	s.set_value(data);
//	return 0;
// }