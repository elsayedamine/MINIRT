#ifndef POOL_H
#define POOL_H

#include "libft.h"
#include <pthread.h>
#include <stdatomic.h>

typedef struct s_task
{
	void	(*f)(void* args);
	void	*args;
} t_task;

typedef struct s_pool
{
	t_list *tasks;
	pthread_t *workers;
	pthread_mutex_t thread;
	int pending;
	int running;
	int count;
	pthread_mutex_t queue_mutex;
	pthread_cond_t queue_cond;
	pthread_mutex_t wait_mutex;
	pthread_cond_t wait_cond;
} t_pool;

#endif