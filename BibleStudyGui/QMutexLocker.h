#ifndef __QMUTEX_HELPER_H
#define __QMUTEX_HELPER_H

#include <QMutex>

namespace BibleStudyGui
{

class QMutexLocker
{
public:
    QMutexLocker(QMutex*	mutex) : 
        m_mutex(mutex)
    {
        m_mutex->lock();
    }

    ~QMutexLocker()
    {
        m_mutex->unlock();
    }

private:
    QMutex* m_mutex;
};

}

#endif // __QMUTEX_HELPER_H
