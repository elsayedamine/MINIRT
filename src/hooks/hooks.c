/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:37:54 by sayed             #+#    #+#             */
/*   Updated: 2025/08/08 23:01:58 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void    hook_manipulation(t_minirt *vars)
{
	mlx_key_hook(vars->win.win, keyhook, vars);
	mlx_hook(vars->win.win, 4, 1L << 2, mouse_click, vars); 
	// mlx_hook(vars->win.mlx, 4, (1L << 2), mouse_down, vars);
	// mlx_hook(vars->win.mlx, 5, (1L << 3), mouse_up, vars);
	// mlx_hook(vars->win.mlx, 6, (1L << 6), mouse_motion, vars);
	mlx_hook(vars->win.win, 17, 1L << 0, quit, vars);
	mlx_loop(vars->win.mlx);
}
