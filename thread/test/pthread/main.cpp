#include <pthread.h>









int main(int argc, char *argv[])
{
    pthread_attr_t tattr;
    pthread_t tid;
    extern void* start_routine(void* arg);
    void* arg;
    int ret;

    ret = pthread_create(&tid, NULL, start_routine, arg);

    ret = pthread_attr_init(&tattr);
    ret = pthread_create(&tid, &tattr, start_routine, arg);






    return 0;
}
