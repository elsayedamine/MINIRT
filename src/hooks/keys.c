/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/13 17:38:15 by sayed            ###   ########.fr       */
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
	
	rot.x = (c == 's') - (c == 'w');
	rot.z = (c == 'a') - (c == 'd');
	rot.y = (c == 'e') - (c == 'q');
	s = vars->selected.obj;
	temp = vec_op_vec(sc_op_vec(s->h * 0.5f, s->o, mul), s->p, add);
	s->o = rotate_z(s->o, rot.z / 10);
	s->o = rotate_x(s->o, rot.x / 10);
	s->o = rotate_y(s->o, rot.y / 10);
	s->tan = rotate_y(s->tan, rot.y / 10);
	s->tan = rotate_x(s->tan, rot.x / 10);
	s->tan = rotate_z(s->tan, rot.z / 10);
	s->bitan = normalize(cross(s->o, s->tan));
	if (s->class == 4 || s->class == 6)
		s->p = vec_op_vec(sc_op_vec(s->h * -0.5f, s->o, mul), temp, add);
	raytracing(vars);
}

int keyhook(int key, t_minirt *vars)
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

void	resize(t_minirt *vars)
{
	int	scale;

	scale = (vars->selected.mouse == 4) - (vars->selected.mouse == 5);
	if (vars->selected.obj->class == SPHERE)
		vars->selected.obj->r += scale;
	if (vars->selected.obj->class == CYLINDER)
	{
		vars->selected.obj->h += scale;
		vars->selected.obj->r += scale;
	}
	if (vars->selected.obj->class == CONE)
	{
		vars->selected.obj->h += scale;
		vars->selected.obj->angle += scale;
	}
	raytracing(vars);
}

void	camera_translation(t_minirt *vars, int c)
{
	t_vec3 trans;

	trans = (t_vec3){(c == 'd') - (c == 'a') / 2.0f,
		(c == 'w') - (c == 's') / 2.0f, (c == 'q') - (c == 'e') / 2.0f};
	vars->cam[vars->cam_id].p = vec_op_vec(vars->cam[vars->cam_id].p, trans, add);
	setup(vars, vars->cam_id);
	raytracing(vars);
}

void	camera_rotation(t_minirt *vars, int c)
{
	vars->cam[vars->cam_id].fw = rotate_x(vars->cam[vars->cam_id].fw, ((c == 'w') - (c == 's')) * 0.05f);
	vars->cam[vars->cam_id].fw = rotate_y(vars->cam[vars->cam_id].fw, ((c == 'd') - (c == 'a')) * 0.05f);
	vars->cam[vars->cam_id].fw = rotate_z(vars->cam[vars->cam_id].fw, ((c == 'q') - (c == 'e')) * 0.05f);
	setup(vars, vars->cam_id);
	raytracing(vars);
}

void	resize_fov(t_minirt *vars)
{
	vars->cam[vars->cam_id].fov += (vars->selected.mouse == 4) - (vars->selected.mouse == 5);
	if (vars->cam[vars->cam_id].fov > 180)
		vars->cam[vars->cam_id].fov = 180;
	if (vars->cam[vars->cam_id].fov < 0)
		vars->cam[vars->cam_id].fov = 0;
	setup(vars, vars->cam_id);
	raytracing(vars);
}

int mouse_click(int button, int x, int y, t_minirt *vars)
{
	t_object *obj = get_hit_info(vars->rays[x][y].origin, vars->rays[x][y].dir, vars).obj;
	if (!obj)
		return (0);
	static int	last_click;
	if (vars->selected.prev <= RIGHT_CLICK)
		last_click = vars->selected.prev;
	vars->selected.obj = obj;
	vars->selected.prev = vars->selected.mouse;
	vars->selected.mouse = button;
	if (last_click == LEFT_CLICK && (button == SCROLL_UP || button == SCROLL_DOWN))
		resize(vars);
	else if (last_click == RIGHT_CLICK && (button == SCROLL_UP || button == SCROLL_DOWN))
		resize_fov(vars);
	return (0);
}
