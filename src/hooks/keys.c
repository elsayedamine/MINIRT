/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/09 08:22:45 by gnxrly           ###   ########.fr       */
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
	t_vec3 ref;
	t_vec3 rot;	
	
	rot.x = (c == 'w') - (c == 's');
	rot.y = (c == 'd') - (c == 'a');
	rot.z = (c == 'q') - (c == 'e');
	
	if (vars->selected.obj->n.y < .999f)
		ref = init_vec(0, 1, 0);
	else
		ref = init_vec(0, 0, -1);
	if (rot.x)
	{
		rotate_z(vars->selected.obj->p, rot.x * 3);
		rotate_z(vars->selected.obj->n, rot.x * 3);
	}
	if (rot.z)
	{
		rotate_x(vars->selected.obj->p, rot.z * 3);
		rotate_x(vars->selected.obj->n, rot.z * 3);		
	}
	if (rot.y)
	{
		vars->selected.obj->facing += rot.y / 10.0f;
		vars->selected.obj->facing = fmod(vars->selected.obj->facing, 1.0);
		if (vars->selected.obj->facing < 0.0)
			vars->selected.obj->facing += 1.0;
	}
	raytracing(vars);
}

int keyhook(int key, t_minirt *vars)
{
	if (key == 65307)
		quit(vars);
	if (key == '\t')
		vars->selected.mouse = 0;
	// printf("use mouse: %d\n", vars->selected.mouse);
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
	// printf("set muose: %d\n", vars->selected.mouse);
	return (0);
}
