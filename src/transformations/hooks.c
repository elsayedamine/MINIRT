/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:37:54 by sayed             #+#    #+#             */
/*   Updated: 2025/08/15 17:15:24 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	keyhook(int key, t_minirt *vars)
{
	int	wasdqe;

	if (key == 65307)
		quit(vars);
	if (key == '\t')
		vars->selected.mouse = NO_CLICK;
	wasdqe = ft_strchr("wasdqe", key) != NULL;
	if (wasdqe && vars->selected.mouse == LEFT_CLICK)
		translation(vars, key);
	else if (wasdqe && vars->selected.mouse == RIGHT_CLICK)
		rotation(vars, key);
	else if (ft_isdigit(key) && vars->cam[key - 48].exist)
		return (setup(vars, key - 48), raytracing(vars), TRUE);
	else if (wasdqe && vars->selected.mouse == NO_CLICK)
		camera_translation(vars, key);
	else if (wasdqe && vars->selected.mouse == MIDDLE_CLICK)
		camera_rotation(vars, key);
	return (TRUE);
}

int	mouse_click(int button, int x, int y, t_minirt *vars)
{
	t_object	*obj;
	static int	last_click;

	obj = get_hit_info(vars->rays[x][y].origin, vars->rays[x][y].dir, vars).obj;
	if (!obj)
		return (0);
	if (vars->selected.prev <= RIGHT_CLICK)
		last_click = vars->selected.prev;
	vars->selected.obj = obj;
	vars->selected.prev = vars->selected.mouse;
	vars->selected.mouse = button;
	if (last_click == LEFT_CLICK && (button == SCROLL_UP || \
		button == SCROLL_DOWN))
		resize(vars);
	else if (last_click == RIGHT_CLICK && (button == SCROLL_UP || \
		button == SCROLL_DOWN))
		resize_fov(vars);
	return (0);
}

void	hook_manipulation(t_minirt *vars)
{
	mlx_key_hook(vars->win.win, keyhook, vars);
	mlx_hook(vars->win.win, 4, 1L << 2, mouse_click, vars);
	mlx_hook(vars->win.win, 17, 1L << 0, quit, vars);
	mlx_loop(vars->win.mlx);
}
