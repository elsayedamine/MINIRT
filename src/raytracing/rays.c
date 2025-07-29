#include <miniRT.h>

typedef t_hit_info		(*t_intersect)(t_vec3 dir, t_object obj);

t_hit_info get_hit_info(t_vec3 dir, t_minirt vars)
{
	t_list *curr;
	t_hit_info hit_info;
	static t_intersect f[] = {
		NULL, NULL,
		intersect_light,
		intersect_sphere,
		intersect_cylinder,
		intersect_plan,
		intersect_last_shape,
	};

	curr = object_list;
	while (curr)
	{
		hit_info = f[curr.type](dir, curr);
		if (hit_info)
			return (hit_info);
		curr = curr->next;
	}
	return (hit_info);
}

int	trace(int count, t_vec3 dir, t_minirt *vars)
{
	int i;
	t_hit_info hit_info;

	i = 0;
	while (i < count)
	{
		hit_info = get_hit_info(dir, *vars); //get hit info, your job
		i++;
		//process hit info, my job
	}
	return ((255 << 24) | ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z);
}

void raytracing(t_minirt *vars)
{
	int i, j, color;

	i = 0;
	while (i < M_WIDTH)
	{
		j = 0;
		while (j < M_HEIGHT)
		{
			color = trace(vars->plane.bounce_count, vars->plane.rays[i][j], vars);
			put_pixel(vars, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
