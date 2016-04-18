#include "readthread.h"
#include "fifo.h"
#include <iostream>
#include <stdio.h>

SaReadThread::SaReadThread()
{

}

SaReadThread::~SaReadThread()
{

}

void SaReadThread::Run()
{
    char temp = '\0';
    if (this->m_pFifo != NULL)
    {
        printf("%s[%d] >> read thread are running.\n",__FILE__,__LINE__);
        this->m_pFifo->Pop();
//        while(1)
//        {
////            if (-1 == this->m_pFifo->Pop(&temp))
////                continue;
////            std::cout << temp;
////            if (temp == 'z')
////                std::cout << std::endl;
//        }
    }
    return;
}

