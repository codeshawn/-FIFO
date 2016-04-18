#include "writethread.h"
#include <stdio.h>
#include <fifo.h>

SaWriteThread::SaWriteThread()
        :m_chtemp('a')
{

}

SaWriteThread::~SaWriteThread()
{

}

void SaWriteThread::Run()
{

    if (this->m_pFifo != NULL)
    {
       // char temp = '\0';
        printf("%s[%d] >> write thread are running.\n",__FILE__,__LINE__);
        this->m_pFifo->Push();
//        while(m_chtemp <= 'z')
//        {
//            if (-1 == this->m_pFifo->Push(m_chtemp))
//                continue;
//            if (m_chtemp == 'z')
//                m_chtemp = 'a';
//            else
//                m_chtemp++;
////            if(this->m_pFifo->Push(m_chtemp) == -1)
////                continue;
////
////            if (!CAS(&m_chtemp,'z','a'))
////            {
////                __sync_fetch_and_add(&m_chtemp,1);
////            }
//        }
    }

    return;
}

