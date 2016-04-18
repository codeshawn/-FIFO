#include "pthreadmanager.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int _mainexit = 0;

void recv_sigint(int a)
{
  _mainexit = 1;
}
int main(void)
{

    signal(SIGINT, recv_sigint);

    SaPthreadManager* pthreadmanager = new SaPthreadManager();

    if (-1 == pthreadmanager->Init())
    {
        printf("%s[%d] >>pthreadmanager Init error.", __FILE__, __LINE__);
        return -1;
    }
    pthreadmanager->Start();

    while (1)
    {
        if(_mainexit)
            break;
        usleep(1000000);
    }
    if (NULL != pthreadmanager)
    {
        pthreadmanager->Stop();
        pthreadmanager->DeInit();
        delete pthreadmanager;
        pthreadmanager = NULL;
    }
    return 0;
}
