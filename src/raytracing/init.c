/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:30:46 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:31:29 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_ray	calc_ray(float u, int y, t_minirt *vars, int cam_id)
{
	t_ray	ray;
	float	v;
	t_vec3	offsetx;
	t_vec3	offsety;

	v = 1 - ((((float)y + .5) / M_HEIGHT) * 2);
	offsetx = sc_op_vec(u * (vars->plane_w / 2), vars->cam[cam_id].rt, mul);
	offsety = sc_op_vec(v * (vars->plane_h / 2), vars->cam[cam_id].up, mul);
	ray.dir = vec_op_vec(vars->cam[cam_id].p, vars->cam[cam_id].fw, add);
	ray.dir = vec_op_vec(ray.dir, offsetx, add);
	ray.dir = vec_op_vec(ray.dir, offsety, add);
	ray.dir = vec_op_vec(ray.dir, vars->cam[cam_id].p, sub);
	ray.dir = normalize(ray.dir);
	ray.origin = vars->cam[cam_id].p;
	return (ray);
}

void	setup_rays(t_minirt *vars, int cam_id)
{
	float	u;
	int		i;
	int		j;

	i = 0;
	j = 0;
	vars->plane_w = 2 * tan((vars->cam[cam_id].fov * RAD) / 2);
	vars->plane_h = vars->plane_w * (float)M_HEIGHT / (float)M_WIDTH;
	vars->rays = malloc(sizeof(t_ray *) * M_WIDTH);
	while (i < M_WIDTH)
	{
		u = (((i + .5) / M_WIDTH) * 2) - 1;
		vars->rays[i] = malloc(sizeof(t_ray) * M_HEIGHT);
		j = 0;
		while (j < M_HEIGHT)
		{
			vars->rays[i][j] = calc_ray(u, j, vars, cam_id);
			j++;
		}
		i++;
	}
}

void	setup(t_minirt *vars, int cam_id)
{
	static int	not_first_time;
	int			i;

	i = -1;
	if (!not_first_time)
	{
		vars->cam[cam_id].rt = rotate_y(vars->cam[cam_id].fw, M_PI / -2);
		vars->cam[cam_id].up = rotate_x(vars->cam[cam_id].fw, M_PI / 2);
		not_first_time = 1;
	}
	else if (not_first_time)
	{
		while (++i < M_WIDTH)
			free(vars->rays[i]);
		free(vars->rays);
	}
	vars->cam_id = cam_id;
	setup_rays(vars, cam_id);
}
