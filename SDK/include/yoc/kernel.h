#ifndef __YOC_KERNEL_H__
#define __YOC_KERNEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <csp.h>

typedef csp_sem_t yoc_sem_t;
typedef csp_mutex_t yoc_mutex_t;

/**
 * Create a task([thread--Rhino&other-kernel][MainLoop--noRTOS])
 *
 * @param[in] name task name, any string
 * @param[in] fn task function
 * @param[in] arg any pointer, will give to your task-function as argument
 * @param[in] stacksize stacksize in bytes
 *
 * @return: task code
 */
int yoc_task_new(const char *name, void (*fn)(void *), void *arg, int stacksize);

/**
 * Create a task([thread--Rhino&other-kernel][MainLoop--noRTOS])
 *
 * @param[in] name task name, any string
 * @param[in] fn task function
 * @param[in] arg any pointer, will give to your task-function as argument
 * @param[in] stacksize stacksize in bytes
 * @param[in] prio priority value, smaller the stronger
 *
 * @return: task code
 */
int yoc_task_new_ext(const char *name, void (*fn)(void *), void *arg,
                     int stacksize, int prio);

/**
 * exit a task
 * @param[in] code the id which yoc_task_new returned
 */
void yoc_task_exit(int code);

/**
 * alloc a mutex
 * @param[in] mutex pointer of mutex object,mutex object must be alloced,
 * hdl pointer in yoc_mutex_t will refer a kernel obj internally
 */
int yoc_mutex_new(yoc_mutex_t *mutex);

/**
 * free a mutex
 * @param[in] mutex mutex object,mem refered by hdl pointer in yoc_mutex_t will
 * be freed internally
 */
void yoc_mutex_free(yoc_mutex_t *mutex);

/**
 * lock a mutex
 * @param[in] mutex mutex object,it contains kernel obj pointer which yoc_mutex_new alloced
 */
uint32_t yoc_mutex_lock(yoc_mutex_t mutex);

/**
 * unlock a mutex
 * @param[in] mutex mutex object,,it contains kernel obj pointer which oc_mutex_new alloced
 */
uint32_t yoc_mutex_unlock(yoc_mutex_t mutex);

/**
 * alloc a semaphore
 * @param[out] sem pointer of semaphore object,semaphore object must be alloced,
 * hdl pointer in yoc_sem_t will refer a kernel obj internally
 * @param[in] count initial semaphore counter
 */
int yoc_sem_new(yoc_sem_t *sem, int32_t count);

/**
 * destroy a semaphore
 * @param[in] sem pointer of semaphore object,mem refered by hdl pointer in yoc_sem_t will be freed internally
 */
void yoc_sem_free(yoc_sem_t *sem);

/**
 * acquire a semaphore
 * @param[in] sem semaphore object,,it contains kernel obj pointer which yoc_sem_new alloced
 * @param[in] timeout waiting until timeout in milliseconds
 */
uint32_t yoc_sem_wait(yoc_sem_t sem, uint32_t timeout);

/**
 * release a semaphore
 * @param[in] sem semaphore object,,it contains kernel obj pointer which yoc_sem_new alloced
 */
void yoc_sem_signal(yoc_sem_t sem);

/**
 * get current time in nano seconds
 * @return elapsed time in nano seconds from system starting
 */
uint64_t yoc_now(void);

/**
 * msleep
 * @param[in] ms sleep time in milliseconds
 */
void yoc_msleep(int ms);
/** thread local storage */
typedef unsigned int yoc_task_key_t;
int yoc_task_key_create(yoc_task_key_t *key);
void yoc_task_key_delete(yoc_task_key_t key);
int yoc_task_setspecific(yoc_task_key_t key, void *vp);
void *yoc_task_getspecific(yoc_task_key_t key);

void *yoc_malloc(int size);
void yoc_free(void *mem);

#ifdef __cplusplus
}
#endif

#endif
