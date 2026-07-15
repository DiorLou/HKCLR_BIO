#ifndef _SINGLETON_H_
#define _SINGLETON_H_

// 单件类
template <class T>
class CSingleton
{
public:
    static T *Instance(bool bAutoClean = true)
    {
        if (NULL == _instance)
        {
            _instance = new T;

            if (bAutoClean)
            {
                static clean cleaner;
            }
        }

        return _instance;
    }

    static void DeleteSingleton()
    {
        if (NULL != _instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }

protected:
    CSingleton()
    {
    }  // 单件类不能被实例化，所以为保护成员
private:
    static T *_instance;

    class clean
    {
    public:
        clean()
        {
        }
        ~clean()
        {
            if (NULL != _instance)
            {
                delete _instance;
                _instance = NULL;
            }
        }
    };
};

template <class T>
T *CSingleton<T>::_instance = 0;

#endif