/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef _PTHREAD_H_
#define _PTHREAD_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "kernel_internal.h"
#include "sched.h"
#include <sys/time.h>
/* ============================ [ MACROS    ] ====================================================== */
#define PTHREAD_CREATE_JOINABLE     0x00
#define PTHREAD_CREATE_DETACHED     0x01

#define PTHREAD_PROCESS_PRIVATE  0
#define PTHREAD_PROCESS_SHARED   1

#define PTHREAD_SCOPE_PROCESS   0
#define PTHREAD_SCOPE_SYSTEM    1

#define PTHREAD_COND_INITIALIZER    { {NULL, NULL}, FALSE }
#define PTHREAD_MUTEX_INITIALIZER   { {NULL, NULL}, FALSE }

/* ============================ [ TYPES     ] ====================================================== */
struct pthread
{
	TaskConstType TaskConst;
	TaskVarType* pTaskVar;
	void *(*start) (void *);
	void* arg;
};
typedef struct pthread* pthread_t;

struct pthread_attr
{
	void*    stack_base;
	uint32_t stack_size;     /* stack size of thread */

	uint8_t priority;        /* priority of thread */
	uint8_t detachstate;     /* detach state */
	uint8_t policy;          /* scheduler policy */
	uint8_t inheritsched;    /* Inherit parent prio/policy */
};
typedef struct pthread_attr pthread_attr_t;

typedef unsigned int pthread_condattr_t;
typedef unsigned int pthread_mutexattr_t;

struct pthread_mutex
{
	TAILQ_HEAD(pthread_mutex_head,TaskVar) head;
	boolean locked;
};
typedef struct pthread_mutex pthread_mutex_t;

struct pthread_cond
{
	TAILQ_HEAD(pthread_cond_head,TaskVar) head;

	unsigned int signals;
};
typedef struct pthread_cond pthread_cond_t;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int state);
int pthread_attr_getdetachstate(pthread_attr_t const *attr, int *state);
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
int pthread_attr_getschedpolicy(pthread_attr_t const *attr, int *policy);
int pthread_attr_setschedparam(pthread_attr_t *attr,struct sched_param const *param);
int pthread_attr_getschedparam(pthread_attr_t const *attr,struct sched_param *param);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stack_size);
int pthread_attr_getstacksize(pthread_attr_t const *attr, size_t *stack_size);
int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack_addr);
int pthread_attr_getstackaddr(pthread_attr_t const *attr, void **stack_addr);
int pthread_attr_setstack(pthread_attr_t *attr,
                          void           *stack_base,
                          size_t          stack_size);
int pthread_attr_getstack(pthread_attr_t const *attr,
                          void                **stack_base,
                          size_t               *stack_size);
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guard_size);
int pthread_attr_getguardsize(pthread_attr_t const *attr, size_t *guard_size);
int pthread_attr_setscope(pthread_attr_t *attr, int scope);
int pthread_attr_getscope(pthread_attr_t const *attr);

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t        *cond,
                           pthread_mutex_t       *mutex,
                           const struct timespec *abstime);

int pthread_create (pthread_t *tid, const pthread_attr_t *attr,
    void *(*start) (void *), void *arg);
void pthread_exit (void *value_ptr);
#endif
