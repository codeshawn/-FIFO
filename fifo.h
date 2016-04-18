#ifndef SA_FIFO_H
#define SA_FIFO_H

#define CAS(a_ptr, a_oldVal, a_newVal) __sync_bool_compare_and_swap(a_ptr, a_oldVal, a_newVal)

#include <pthread.h>
#include <queue>
#include <semaphore.h>

class SaFifo{

public:
    SaFifo();
    ~SaFifo();

    int Init(int nMaxPushNum);
    int DeInit(void);

    int Push();
    int Pop();

    int CountToIndex(int count);

    void SetMaxPushNum(int nMaxPushNum);

private:
    int                         m_nFifoLen;
    bool                        m_bInitOk;
    int*                       m_chQueue;
    volatile char               m_chTemp;
    volatile int                m_nWriteIndex;
    volatile int                m_nReadIndex;
    volatile int                m_nMaxReadIndex;
    pthread_mutexattr_t         m_lockAttr;
    pthread_mutex_t             m_lockQueue;
};

#endif
