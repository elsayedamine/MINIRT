/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:37:54 by sayed             #+#    #+#             */
/*   Updated: 2025/08/08 17:37:55 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void    hook_manipulation(t_minirt *vars)
{
	mlx_key_hook(vars->win.win, keyhook, vars);
	mlx_hook(vars->win.win, 17, 1L << 0, quit, vars);
	mlx_loop(vars->win.mlx);
}
