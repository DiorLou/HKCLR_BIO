#ifndef CLHBCircleBuffer_H
#define CLHBCircleBuffer_H
/********************************************************************
version:	深圳深信服电子科技有限公司
created:	5:3:2008   10:15
filename: 	CLHBCircleBuffer.h
author:		lhb

purpose:	环形缓冲区操作类,用作数据流缓冲池
*********************************************************************/

/*用法:
CLHBCircleBuffer cbuf(1024);
或:
CLHBCircleBuffer cbuf;
cbuf.init(1024);
...
DoSomething
*/
#include <mutex>

typedef unsigned int uint;

class CLHBCircleBuffer
{
public:
    enum
    {
        all = 0xffffffff
    };
    CLHBCircleBuffer()
    {
        m_buf = NULL;
        m_head = m_tail = m_len = 0;
    }
    // 初始带长度
    CLHBCircleBuffer(uint buflen)
    {
        m_buf = NULL;
        m_head = m_tail = m_len = 0;

        init(buflen);
    }

    // 析构
    ~CLHBCircleBuffer()
    {
        free();
    }

public:
    inline bool Init(uint buflen)
    {
        return init(buflen);
    }
    inline void Reset()
    {
        reset();
    }
    inline uint Put(void *buf, uint buflen)
    {
        return put(buf, buflen);
    }
    inline uint Get(void *buf, uint buflen)
    {
        return get(buf, buflen);
    }
    inline uint Peek(void *buf, uint buflen)
    {
        return peek(buf, buflen);
    }
    inline uint PeekExt(void *buf, uint offset, uint buflen)
    {
        return peek_ext(buf, offset, buflen);
    }
    inline uint Erase(uint len)
    {
        return del(len);
    }
    inline uint FreeCount()
    {
        return free_size();
    }
    inline uint DataCount()
    {
        return size();
    }
    inline uint Count()
    {
        return free_size() + size();
    }
    inline void MovePos(uint len)
    {
        move_pos(len);
    }

private:
    void free()
    {
        if (m_buf)
            delete[] m_buf;
        m_buf = 0;
    }
    void *mem_ptr()
    {
        return (char *)m_buf;
    }

    /** 重设头尾指针为起点
     */
    void reset()
    {
        m_head = m_tail = 0;
    }
    /** 初始化环形缓冲区
    @param mapbuf:映射的内存地址
    @param buflen: 内存空间大小
    */
    bool init(uint buflen)
    {
        buflen = buflen + 1;  // 留一个判断表满

        if (m_buf)
            ::free(m_buf);
        m_buf = new char[buflen];
        if (!m_buf)
            return false;
        m_len = buflen;
        return true;
    }

    /** 从环形缓冲区取数据
    @return : 实际取到的数据长度
    */
    uint get(void *buf, uint len)
    {
        _mutex.lock();
        uint data_size = size();
        if (len > data_size)
            len = data_size;

        if (m_tail < m_head)
        {
            if ((m_len - m_head) >= len)
            {
                memcpy(buf, &m_buf[m_head], len);
                m_head += len;
            }
            else
            {
                int _tail = m_len - m_head;  // 尾锟斤拷锟斤拷莩锟斤拷锟?

                char *buf1 = (char *)buf;
                memcpy(buf, &m_buf[m_head], _tail);
                memcpy(&buf1[_tail], m_buf, len - _tail);
                m_head = len - (m_len - m_head);
            }
        }
        else
        {
            memcpy(buf, &m_buf[m_head], len);
            m_head += len;
        }
        _mutex.unlock();
        return len;
    }
    /** 往环形缓冲区加数据
    @return : 实际添加的数据长度
    */
    uint put(void *buf, uint len)
    {
        _mutex.lock();
        uint space_size = free_size();

        // freeSize()

        if (len > space_size)
        {
            len = space_size;
        }

        char *buf1 = (char *)buf;
        if (m_tail < m_head)
        {
            memcpy(&m_buf[m_tail], buf, len);
            m_tail += len;
        }
        else  // m_head <= m_tail
        {
            if ((m_len - m_tail) >= len)
            {
                memcpy(&m_buf[m_tail], buf, len);
                m_tail += len;
            }
            else
            {
                int _tail = m_len - m_tail;  //
                memcpy(&m_buf[m_tail], buf, _tail);
                memcpy(m_buf, &buf1[_tail], len - _tail);
                m_tail = len - _tail;
            }
        }
        _mutex.unlock();
        return len;
    }

    /** 环形缓冲区中数据的长度
     */
    uint size()
    {
        if (m_tail < m_head)
            return m_len - (m_head - m_tail);
        else
            return m_tail - m_head;
    }
    /** 环形缓冲区中的剩余空间长度
     */
    uint free_size()
    {
        if (m_tail < m_head)
            return m_head - m_tail - 1;
        else
            return m_len - (m_tail - m_head) - 1;
    }

    /** 取缓冲区中的数据但不移动缓冲区的指针(偷窥?)
    @return 实际可偷窥的数据长度
    */
    uint peek(void *buf, uint len)
    {
        _mutex.lock();
        uint data_size = size();
        if (len > data_size)
            len = data_size;

        if (m_tail < m_head)
        {
            if ((m_len - m_head) >= len)
            {
                memcpy(buf, &m_buf[m_head], len);
            }
            else
            {
                int _tail = m_len - m_head;  // 尾锟斤拷锟斤拷莩锟斤拷锟?

                char *buf1 = (char *)buf;
                memcpy(buf, &m_buf[m_head], _tail);
                memcpy(&buf1[_tail], m_buf, len - _tail);
            }
        }
        else
        {
            memcpy(buf, &m_buf[m_head], len);
        }
        _mutex.unlock();
        return len;
    }

    uint peek_ext(void *buf, uint offset, uint len)
    {
        if (size() <= offset)
            return 0;

        _mutex.lock();
        uint data_size = size() - offset;
        if (len > data_size)
            len = data_size;

        if (m_tail < (m_head + offset))
        {
            if ((m_len - (m_head + offset)) >= len)
            {
                memcpy(buf, &m_buf[m_head] + offset, len);
            }
            else
            {
                int _tail = m_len - m_head - offset;

                char *buf1 = (char *)buf;
                memcpy(buf, &m_buf[m_head] + offset, _tail);
                memcpy(&buf1[_tail], m_buf, len - _tail);
            }
        }
        else
        {
            memcpy(buf, &m_buf[m_head] + offset, len);
        }
        _mutex.unlock();
        return len;
    }

    /** 删除缓冲区中的数据
    @param len:删除的长度
    @return :实际删除的长度
    */
    uint del(uint len)
    {
        _mutex.lock();
        uint data_size = size();
        if (len > data_size)
            len = data_size;

        // move head pointer
        if (m_tail < m_head)
        {
            if ((m_len - m_head) >= len)
            {
                m_head += len;
            }
            else
            {
                m_head = len - (m_len - m_head);
            }
        }
        else
        {
            m_head += len;
        }
        _mutex.unlock();
        return len;
    }

    /** 将头len长数据,移到尾部
    @param len:移到尾部的长度
    @return :
    */
    void move_pos(uint len)
    {
        char *pBuf = new char[len];
        get(pBuf, len);
        put(pBuf, len);
        delete[] pBuf;
    }

private:
    uint m_len;
    uint m_head;
    uint m_tail;
    char *m_buf;
    std::mutex _mutex;
};

#endif
