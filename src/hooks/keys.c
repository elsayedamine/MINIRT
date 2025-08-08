/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/08 23:05:37 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void translation(t_minirt *vars, int c)
{
	t_vec3 trans;

	trans = init_vec((c == 'a') - (c == 'd'),
		(c == 'w') - (c == 's'), (c == 'q') - (c == 'e'));
	vars->selected.obj->p = vec_op_vec(vars->selected.obj->p, trans, add);
	raytracing(vars);
}

void rotation(t_minirt *vars, int c)
{
	vars->selected.obj->p = rotate_x(vars->selected.obj->p, ((c == 'a') - (c == 'd')) * 3);
	vars->selected.obj->p = rotate_y(vars->selected.obj->p, ((c == 'w') - (c == 's')) * 3);
	vars->selected.obj->p = rotate_z(vars->selected.obj->p, ((c == 'q') - (c == 'e')) * 3);
	raytracing(vars);
}

int keyhook(int key, t_minirt *vars)
{
	if (key == 65307)
		quit(vars);
	if (key == 36)
		vars->selected.mouse = 0;
	if (ft_strchr("wasdqe", key) && vars->selected.mouse == LEFT_CLICK)
		translation(vars, key);
	if (ft_strchr("wasdqe", key) && vars->selected.mouse == RIGHT_CLICK)
		rotation(vars, key);
    return (TRUE);
}

int mouse_click(int button, int x, int y, t_minirt *vars)
{
	t_object *obj = get_hit_info(vars->rays[x][y].origin, vars->rays[x][y].dir, vars).obj;
	if (!obj)
		return (0);
	vars->selected.obj = obj;
	vars->selected.mouse = button;
	return (0);
}
