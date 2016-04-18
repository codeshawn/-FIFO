#ifndef SA_READTHREAD_H
#define SA_READTHREAD_H
#include "thread.h"

class SaFifo;
class SaReadThread:public SaIThread
{
public:
    SaReadThread();
    ~SaReadThread();
    virtual void Run();
};

#endif
