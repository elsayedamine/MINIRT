/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:52:35 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:38:34 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	broadcast(t_pool *pool)
{
	pthread_mutex_lock(&pool->wait_mutex);
	pthread_cond_broadcast(&pool->wait_cond);
	pthread_mutex_unlock(&pool->wait_mutex);
}

void	*worker(void *args)
{
	t_pool	*pool;
	t_list	*curr;
	t_task	task;

	pool = (t_pool *)args;
	while (1)
	{
		pthread_mutex_lock(&pool->queue_mutex);
		while (!pool->tasks && pool->running)
			pthread_cond_wait(&pool->queue_cond, &pool->queue_mutex);
		if (!pool->running)
			return (pthread_mutex_unlock(&pool->queue_mutex), NULL);
		curr = pool->tasks;
		pool->tasks = curr->next;
		task = *(t_task *)curr->content;
		pthread_mutex_unlock(&pool->queue_mutex);
		if (!curr)
			continue ;
		task.f(task.args);
		free_args(task.args);
		ft_lstdelone(curr, free);
		if (atomic_fetch_sub(&pool->pending, 1) == 1)
			broadcast(pool);
	}
	return (NULL);
}

void	add_task(t_pool *pool, void (*f)(void *args), void *args)
{
	t_task	*task;

	pthread_mutex_lock(&pool->queue_mutex);
	if (!pool->running)
		return ;
	task = malloc(sizeof(t_task));
	task->f = f;
	task->args = args;
	ft_lstadd_back(&pool->tasks, ft_lstnew((void *)task));
	atomic_fetch_add(&pool->pending, 1);
	pthread_cond_signal(&pool->queue_cond);
	pthread_mutex_unlock(&pool->queue_mutex);
}
