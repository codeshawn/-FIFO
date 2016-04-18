#ifndef SA_I_THREAD_H
#define SA_I_THREAD_H
#include <pthread.h>

class SaFifo;
class SaIThread
{
public:
    SaIThread();
    virtual ~SaIThread();
    int start(SaFifo* fifo);
    static void* gThreadFun(void* param);

    virtual void Run() = 0;

    SaFifo*     m_pFifo;

private:
    pthread_t   m_nPthreadId;

};

#endif
