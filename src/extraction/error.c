/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 16:13:53 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	cleanup(t_minirt *vars, int n)
{
	if (1 & n)
		ft_lstclear(&vars->members, free);
}

int	throw_error(int err)
{
	if (err <= CONE && err >= 0)
		printfd(2, "Error\n\tUndefined data for %s element!\n", g_strs[err]);
	if (err == ERR)
		printfd(2, "Error\n\tUndefined data entry!\n");
	if (err == TOO_MANY_CAM)
		printfd(2, "Error\n\tToo many cameras!\n");
	return (1);
}
