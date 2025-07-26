/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:27:22 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 16:32:27 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_window(t_minirt *vars)
{
	vars->win.mlx = mlx_init();
	if (!vars->win.mlx)
		return (printfd(2, "Failure in X connection!\n"), exit(2));
	vars->win.win = mlx_new_window(vars->win.mlx, M_WIDTH, M_HEIGHT,
			"Hello world!");
	vars->win.img = mlx_new_image(vars->win.mlx, M_WIDTH, M_HEIGHT);
	if (!vars->win.img)
		return (printfd(2, "Failure in creating image!\n"), exit(2));
	vars->win.addr = mlx_get_data_addr(vars->win.img,
			&vars->win.bits_per_pixel, &vars->win.line_length,
			&vars->win.endian);
}
