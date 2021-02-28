#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <sys/resource.h>


void* hello(void* s)
{
    int i, ret;
    int policy;
    int old_prio, new_prio;
    int max_prio, min_prio;
    struct sched_param param;
    std::chrono::seconds sec(2);

    ret = pthread_getschedparam(pthread_self(), &policy, &param);

    if (ret) {
        std::cout << "Error: " << ret << " failed to get scheduling parameters\n";
    }

    std::cout << policy << " " << param.sched_priority <<'\n';

    param.sched_priority = 1;
    ret = pthread_setschedparam(pthread_self(), policy, &param);

    old_prio = getpriority(PRIO_PROCESS, pthread_self());
    std::cout << "priority: " << old_prio <<'\n';

    max_prio = sched_get_priority_max(SCHED_OTHER); 
    min_prio = sched_get_priority_min(SCHED_OTHER); 
    std::cout << "maximum priority: " << max_prio << ", minimum priority: " << min_prio << '\n';

    if (ret) {
        std::cout << "Error: " << ret << " failed to set scheduling parameters\n";
    }

    ret = pthread_getschedparam(pthread_self(), &policy, &param);

    for (i = 0; i < 10; i++) {
        std::cout << "hello! " << (char *)s << policy << " " << param.sched_priority <<'\n';
        std::this_thread::sleep_for(sec);
    }

    return 0;
}

int main()
{
    pthread_t tid;
    int ret;
    int i;
    std::chrono::seconds sec(1);

    ret = pthread_create(&tid, nullptr, hello, const_cast<char *>("World"));

    if (ret) {
        std::cout << "Error " << ret << " : cannot create new thread.\n";
    }

    for (i = 0; i < 10; i++) {
        std::cout << "I am main thread\n";
        std::this_thread::sleep_for(sec);
    }

    return 0;
}
