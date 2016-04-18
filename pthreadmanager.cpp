#include "pthreadmanager.h"
#include "fifo.h"
#include "writethread.h"
#include "readthread.h"

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

SaPthreadManager::SaPthreadManager()
            :m_bInitOk(false)
            ,m_bStartOk(false)
            ,m_pFifo(NULL)
            ,m_pWrite(NULL)
            ,m_pWriteThree(NULL)
            ,m_pRead(NULL)
{

}

SaPthreadManager::~SaPthreadManager()
{
    DeInit();
}

int SaPthreadManager::Init()
{
    if (m_bInitOk)
    {
        printf("%s[%d] >> error: can't init twice.\n", __FILE__, __LINE__);
        return -1;
    }
    m_pFifo = new SaFifo();

    if (m_pFifo->Init(5) < 0 )
    {
        printf("%s[%d] >> SaPthreadManager Init error.\n",__FILE__,__LINE__);
        return -1;
    }
    m_pWrite = new SaWriteThread();
    m_pWriteTwo = new SaWriteThread();
    m_pWriteThree = new SaWriteThread();
    m_pRead = new SaReadThread();
    m_pReadTwo = new SaReadThread();

    m_bInitOk = true;
    return 0;
}

void SaPthreadManager::Start()
{
    if (m_bStartOk)
    {
        printf("%s[%d] >> error: can't start twice.\n", __FILE__, __LINE__);
        return;
    }
    m_pWrite->start(m_pFifo);
    m_pWriteTwo->start(m_pFifo);
    m_pWriteThree->start(m_pFifo);
    m_pRead->start(m_pFifo);
//    m_pReadTwo->start(m_pFifo);

    m_bStartOk = true;
}

void SaPthreadManager::Stop()
{
    if (m_bStartOk)
        m_bStartOk = false;
}

int SaPthreadManager::DeInit()
{
    Stop();

    if (m_pWrite != NULL)
    {
        delete m_pWrite;
        m_pWrite = NULL;
    }

    if (m_pWriteTwo != NULL)
    {
        delete m_pWriteTwo;
        m_pWriteTwo = NULL;
    }

    if (m_pRead != NULL)
    {
        delete m_pRead;
        m_pRead = NULL;
    }

    if (m_pReadTwo != NULL)
    {
        delete m_pReadTwo;
        m_pReadTwo = NULL;
    }

    if (m_pFifo != NULL)
    {
        m_pFifo->DeInit();
        delete m_pFifo;
        m_pFifo = NULL;
    }


    m_bInitOk = false;
    return 0;
}
