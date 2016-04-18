#ifndef SA_PTHREAD_MANAGER_H
#define SA_PTHREAD_MANAGER_H
#include <pthread.h>

class SaFifo;
class SaWriteThread;
class SaReadThread;
class SaPthreadManager
{
public:
    SaPthreadManager();
    ~SaPthreadManager();
    int Init();
    void Start();
    void Stop();
    int DeInit();

private:
    bool                m_bInitOk;
    bool                m_bStartOk;
    SaFifo*             m_pFifo;
    SaWriteThread*      m_pWrite;
    SaWriteThread*      m_pWriteTwo;
    SaWriteThread*      m_pWriteThree;
    SaReadThread*       m_pRead;
    SaReadThread*       m_pReadTwo;
};
#endif
