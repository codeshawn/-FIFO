#include "thread.h"
#include <stdio.h>

SaIThread::SaIThread()
    :m_nPthreadId(0)
    ,m_pFifo(NULL)
{

}
SaIThread::~SaIThread()
{
    pthread_cancel(m_nPthreadId);
    pthread_join(m_nPthreadId,NULL);

}

int SaIThread::start(SaFifo* fifo)
{
    if (NULL == fifo)
    {
        printf("%s[%d] >> thread start error!\n",__FILE__,__LINE__);
        return -1;
    }
    m_pFifo = fifo;
    pthread_create(&m_nPthreadId,NULL,gThreadFun,(void*)this);
    return 0;
}

void* SaIThread::gThreadFun(void* param)
{
    SaIThread* pSelf = (SaIThread*) param;
    if (NULL == pSelf)
    {
        printf("%s[%d] >> gThreadFun Create error.",__FILE__,__LINE__);
        return NULL;
    }

    pSelf->Run();
    return NULL;
}

