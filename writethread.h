#ifndef SA_WRITETHREAD_H
#define SA_WRITETHREAD_H
#include "thread.h"

class SaFifo;
class SaWriteThread:public SaIThread
{
public:
    SaWriteThread();
    ~SaWriteThread();
    virtual void Run();

private:
    char m_chtemp;
};

#endif
