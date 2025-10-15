#ifndef PTHREAD_UTILS_H_INCLUDED
#define PTHREAD_UTILS_H_INCLUDED

int pthread_create_detached(void* (*func)(void*), void* arg);

#endif // PTHREAD_UTILS_H_INCLUDED
