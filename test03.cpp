#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>


void* hello(void* s)
{
    int i, j;
    pid_t tid;
    struct rlimit limit;

    limit.rlim_cur = 40;
    limit.rlim_max = 40;

    setrlimit(RLIMIT_NICE, &limit);

    tid = gettid();
    setpriority(PRIO_PROCESS, tid, -20);

    std::cout << "thread " << tid << " : priority " << getpriority(PRIO_PROCESS, tid) << '\n';

    while (1) {
        std::cout << "==================== child thread =====================" << tid << '\n';
    }

    return 0;
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    struct sched_param param;

    int ret;

    pthread_attr_init(&attr);
    param.sched_priority = 1;

    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam(&attr, &param);

    ret = pthread_create(&tid, nullptr, hello, const_cast<char *>("World"));

    if (ret) {
        std::cout << "Error " << ret << " : cannot create new thread.\n";
    }

    tid = gettid();

    while (1) {
        std::cout << "main thread " << tid << " exit\n";
    }

    return 0;
}
