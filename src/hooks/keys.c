/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/09 17:55:02 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void translation(t_minirt *vars, int c)
{
	t_vec3 trans;

	trans = (t_vec3){(c == 'd') - (c == 'a') / 2.0f,
		(c == 'w') - (c == 's') / 2.0f, (c == 'q') - (c == 'e') / 2.0f};
	vars->selected.obj->p = vec_op_vec(vars->selected.obj->p, trans, add);
	raytracing(vars);
}


void rotation(t_minirt *vars, int c)
{
	t_object *s;
	t_vec3 rot;
	t_vec3 temp;
	
	rot.x = (c == 'w') - (c == 's');
	rot.z = (c == 'd') - (c == 'a');
	rot.y = (c == 'q') - (c == 'e');
	s = vars->selected.obj;
	if (rot.x || rot.z)
	{
		// if (s->class == 4 || s->class == 6)
		// {
		// 	temp = vec_op_vec(s->p, sc_op_vec(s->h * 0.5f, s->o, mul), add);
		// 	temp = rotate_z(temp, rot.z / 10);
		// 	temp = rotate_x(temp, rot.x / 10);
		// 	s->p = vec_op_vec(temp, sc_op_vec(s->h * 0.5f, s->o, mul), sub);
		// }
		s->o = rotate_z(s->o, rot.z / 10);
		s->o = rotate_x(s->o, rot.x / 10);
		set_object_vec(s);		
	}
	if (rot.y)
	{
		s->facing += rot.y / 10.0f;
		s->facing = fmod(s->facing, 1.0);
		if (s->facing < 0.0)
			s->facing += 1.0;
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
		printf("%d\n", key);
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
