/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:33:58 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:36:43 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h> 

void	pool_wait(t_pool *pool)
{
	pthread_mutex_lock(&pool->wait_mutex);
	while (atomic_load(&pool->pending) > 0)
		pthread_cond_wait(&pool->wait_cond, &pool->wait_mutex);
	pthread_mutex_unlock(&pool->wait_mutex);
}

void	init_pool(t_pool *pool)
{
	int	i;

	pool->tasks = NULL;
	pthread_mutex_init(&pool->queue_mutex, NULL);
	pthread_mutex_init(&pool->wait_mutex, NULL);
	pthread_cond_init(&pool->queue_cond, NULL);
	pthread_cond_init(&pool->wait_cond, NULL);
	pthread_mutex_init(&pool->thread, NULL);
	pool->running = 1;
	pool->pending = 0;
	pool->count = sysconf(_SC_NPROCESSORS_ONLN);
	if (pool->count < 1)
		pool->count = 4;
	pool->workers = malloc(sizeof(pthread_t) * pool->count);
	if (!pool->workers)
		pool_destroy(pool);
	i = -1;
	while (++i < pool->count)
		pthread_create(pool->workers + i, NULL, worker, (void *)pool);
}

void	pool_destroy(t_pool *pool)
{
	int	i;

	pthread_mutex_lock(&pool->queue_mutex);
	pool->running = 0;
	pthread_cond_broadcast(&pool->queue_cond);
	pthread_mutex_unlock(&pool->queue_mutex);
	i = -1;
	while (++i < pool->count)
		pthread_join(pool->workers[i], NULL);
	pthread_mutex_destroy(&pool->queue_mutex);
	pthread_mutex_destroy(&pool->wait_mutex);
	pthread_cond_destroy(&pool->queue_cond);
	pthread_cond_destroy(&pool->wait_cond);
	pthread_mutex_destroy(&pool->thread);
	free(pool->workers);
	ft_lstclear(&pool->tasks, free);
}
