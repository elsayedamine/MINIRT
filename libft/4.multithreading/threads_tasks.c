/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_tasks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:35:44 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:35:51 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	free_args(void **args)
{
	void	**cpy;

	cpy = args;
	while (*cpy)
		free(*cpy++);
	free(args);
}

void	*mk_args(int count, ...)
{
	va_list	args;
	int		i;
	void	**arr;
	int		size;
	void	*ptr;

	arr = malloc(sizeof(void *) * (count + 1));
	if (!arr)
		return (NULL);
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(args, void *);
		size = va_arg(args, unsigned long);
		arr[i] = malloc(size);
		ft_memcpy(arr[i], ptr, size);
		i++;
	}
	arr[i] = NULL;
	va_end(args);
	return (arr);
}
