/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/09 00:02:04 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void translation(t_minirt *vars, int c)
{
	t_vec3 trans;

	trans = init_vec((c == 'd') - (c == 'a') / 2.0f,
		(c == 'w') - (c == 's') / 2.0f, (c == 'q') - (c == 'e') / 2.0f);
	vars->selected.obj->p = vec_op_vec(vars->selected.obj->p, trans, add);
	raytracing(vars);
}

void rotation(t_minirt *vars, int c)
{
	vars->selected.obj->p = rotate_x(vars->selected.obj->p, ((c == 'd') - (c == 'a')) * 3);
	vars->selected.obj->p = rotate_y(vars->selected.obj->p, ((c == 'w') - (c == 's')) * 3);
	vars->selected.obj->p = rotate_z(vars->selected.obj->p, ((c == 'q') - (c == 'e')) * 3);
	raytracing(vars);
}

int keyhook(int key, t_minirt *vars)
{
	if (key == 65307)
		quit(vars);
	if (key == '\t')
		vars->selected.mouse = 0;
	if (ft_strchr("wasdqe", key) && vars->selected.mouse == LEFT_CLICK)
		translation(vars, key);
	if (ft_strchr("wasdqe", key) && vars->selected.mouse == RIGHT_CLICK)
		rotation(vars, key);
	// i will do somthing for the camera here
	if (ft_isdigit(key) && vars->cam[key - 48].exist)
	{
		setup(vars, key - 48);
		raytracing(vars);
	}
	// guess i did hhhhhhh
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
