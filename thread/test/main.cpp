#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* thread(void* ptr)
{
    int i = 0;
    for (i = 0; i < 3; i++) {
        sleep(1);
        cout << "This is a pthread...." << endl;
    }

    return 0;
}

int main()
{
    pthread_attr_t attr;
    pthread_t id;
    sched_param param;
    int newprio = 20;

    pthread_attr_init(&a&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    int ret = pthread_create(&id, &attr, thread, NULL);
    if (ret) {
        cout << "This is a pthread." << endl;
        return 1;
    }
    int i = 0;
    for (i = 0; i < 3; i++) {
        cout << "This is the main process." << endl;

        sleep(1);

    }
    pthread_join(id, NULL);

    return 0;
}
