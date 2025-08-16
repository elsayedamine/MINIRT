/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:15:45 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 17:11:25 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	camera_translation(t_minirt *vars, int c)
{
	t_vec3	trans;

	trans = (t_vec3){(c == 'd') - (c == 'a') / 2.0f,
		(c == 'w') - (c == 's') / 2.0f, (c == 'q') - (c == 'e') / 2.0f};
	vars->cam[vars->cam_id].p = vec_op_vec(vars->cam[vars->cam_id].p, \
		trans, add);
	setup(vars, vars->cam_id);
	raytracing(vars);
}

void	camera_rotation(t_minirt *vars, int c)
{
	vars->cam[vars->cam_id].fw = rotate_x(vars->cam[vars->cam_id].fw, \
		((c == 'w') - (c == 's')) / 10);
	vars->cam[vars->cam_id].fw = rotate_y(vars->cam[vars->cam_id].fw, \
		((c == 'd') - (c == 'a')) / 10);
	vars->cam[vars->cam_id].fw = rotate_z(vars->cam[vars->cam_id].fw, \
		((c == 'q') - (c == 'e')) / 10);
	setup(vars, vars->cam_id);
	raytracing(vars);
}

void	resize_fov(t_minirt *vars)
{
	vars->cam[vars->cam_id].fov += (vars->selected.mouse == 4) - \
		(vars->selected.mouse == 5);
	if (vars->cam[vars->cam_id].fov > 180)
		vars->cam[vars->cam_id].fov = 180;
	if (vars->cam[vars->cam_id].fov < 0)
		vars->cam[vars->cam_id].fov = 0;
	setup(vars, vars->cam_id);
	raytracing(vars);
}
