#include "fifo.h"
#include <stdio.h>
#include <iostream>

SaFifo::SaFifo()
    :m_nFifoLen(0)
    ,m_bInitOk(false)
    ,m_nWriteIndex(0)
    ,m_nReadIndex(0)
    ,m_nMaxReadIndex(0)
    ,m_chTemp('a')
{
}

SaFifo::~SaFifo()
{
    DeInit();
}

int SaFifo::Init(int nMaxPushNum)
{
    if (m_bInitOk)
    {
        printf("%s[%d] >> error: can't init twice.\n", __FILE__, __LINE__);
        return -1;
    }

    int nResultInit = 0;
    nResultInit = pthread_mutexattr_init(&m_lockAttr);
    if (0 != nResultInit) {
        printf("%s[%d] >> error: init lock error[%d].", __FILE__, __LINE__, nResultInit);
        return -1;
    }

    nResultInit = pthread_mutex_init(&m_lockQueue, &m_lockAttr);
    if (0 != nResultInit) {
        printf("%s[%d] >> error: init lock error[%d].", __FILE__, __LINE__, nResultInit);
        return -1;
    }

    m_chQueue = new int[nMaxPushNum];

    for(int i = 0;i<nMaxPushNum;i++)
        m_chQueue[i] = 0;
    m_nFifoLen = nMaxPushNum;
    m_bInitOk = true;
    return 0;
}

int SaFifo::DeInit()
{
    pthread_mutexattr_destroy(&m_lockAttr);
    pthread_mutex_destroy(&m_lockQueue);

    delete[] m_chQueue;
    m_chQueue = NULL;

    m_bInitOk = false;
    return 0;
}

int SaFifo::CountToIndex(int count)
{
    return (count % m_nFifoLen);
}

int SaFifo::Push()
{

    if (!m_bInitOk)
    {
      printf("%s[%d] >> error: not init ok.\n", __FILE__, __LINE__);
      return -1;
    }

    int CurrentWriteIndex = 0,CurrentReadIndex = 0;
    char CurrentWriteData ='\0';
    do{
        CurrentWriteIndex = m_nWriteIndex;
        CurrentReadIndex = m_nReadIndex;
        CurrentWriteData = m_chTemp;
        if (CountToIndex(CurrentWriteIndex + 1) == CountToIndex(CurrentReadIndex))
        {
           // printf("%s[%d] >> the queue is full.\n", __FILE__, __LINE__);
           continue;
        }

        m_chQueue[CountToIndex(CurrentWriteIndex)] =CountToIndex(CurrentWriteIndex);


        if (!CAS(&m_nWriteIndex,CurrentWriteIndex,(CountToIndex(CurrentWriteIndex + 1))))
            continue;
 /*       if (CurrentWriteData == 'z')
        {
            if (!CAS(&m_chTemp,CurrentWriteData,'a'))
               continue;
        }
        else
        {
            if (!CAS(&m_chTemp,CurrentWriteData,(CurrentWriteData+1)))
            {
                __sync_fetch_and_sub(&m_nWriteIndex,1);
                continue;
            }
        }
*/

        while(!CAS(&m_nMaxReadIndex,CurrentWriteIndex,(CountToIndex(CurrentWriteIndex + 1))))
        {
            sched_yield();
        }


    }while(1);

    return 0;
}

int SaFifo::Pop()
{
    if (!m_bInitOk)
    {
        printf("%s[%d] >> error: not init ok.\n", __FILE__, __LINE__);
        return -1;
    }
    int CurrentReadIndex = 0,CurrentMaxReadIndex = 0;
    int outdata = 0;

    do{
        CurrentReadIndex        = m_nReadIndex;
        CurrentMaxReadIndex     = m_nMaxReadIndex;

        if (CountToIndex(CurrentReadIndex) == CountToIndex(CurrentMaxReadIndex))
        {
          //  printf("%s[%d] >> the queue is empty.\n", __FILE__, __LINE__);
           // return -1;
            continue;
        }

        //pthread_mutex_lock(&m_lockQueue);
        outdata = CountToIndex(m_chQueue[CountToIndex(CurrentReadIndex)]);
        //pthread_mutex_unlock(&m_lockQueue);

        if(!CAS(&m_nReadIndex,CurrentReadIndex,(CountToIndex(CurrentReadIndex+1))))
            continue;

       // pthread_mutex_lock(&m_lockQueue);
        std::cout << CurrentReadIndex;
        if (CurrentReadIndex == 4)
            std::cout << std::endl;
       // pthread_mutex_unlock(&m_lockQueue);

//        pthread_mutex_lock(&m_lockQueue);
//        if (m_chQueue[CountToIndex(CurrentReadIndex)] == outdata)
//        {
//            std::cout << outdata;
//            if (outdata == 'z')
//                std::cout << std::endl;
//        }
//        else
//        {
//            __sync_fetch_and_sub(&m_nReadIndex,1);
//            printf("%s[%d] >> ------------------------------------------------.\n", __FILE__, __LINE__);
//
//        }
//        pthread_mutex_unlock(&m_lockQueue);

    }while(1);
   // assert(0);
    return -1;
}

void SaFifo::SetMaxPushNum(int nMaxPushNum)
{
    m_nFifoLen = nMaxPushNum;
}

