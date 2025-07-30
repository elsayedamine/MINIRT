#include <miniRT.h>

t_hit_info get_hit_info(t_vec3 origin, t_vec3 dir, t_minirt *vars)
{
	t_list				*curr;
	t_object			*obj;
	t_hit_info			hit_info;
	static t_intersect	f[] = {
		intersect_light,
		intersect_sphere,
		intersect_cylinder,
		intersect_plan,
		intersect_last_shape,
	};

	curr = vars->members;
	while (curr)
	{
		obj = (t_object *)curr->content;
		hit_info = f[obj->class - 2](origin, dir, obj);
		if (hit_info.light)
			return (hit_info);
		curr = curr->next;
	}
	return (hit_info);
}

t_ray new_ray(t_vec3 pos, t_vec3 normal)
{
	t_ray new;

	new.dir = init_vec(rrand(&pos, -1, 1), rrand(&pos, -1, 1), rrand(&pos, -1, 1));
	if (dot(new.dir, normal) < 0)
		new.dir = sc_op_vec(-1, new.dir, mul);
	new.dir = normalize(vec_op_vec(normalize(new.dir), normal, add));
	new.origin = pos;
	return (new);
}

int	trace(t_minirt *vars, t_ray ray, int count)
{
	t_color light;
	t_color color;
	t_hit_info hit_info;
	int i;

	i = 0;
	light = init_color(0, 0, 0);
	color = init_color(255, 255, 255);
	while (i < count)
	{
		hit_info = get_hit_info(ray.origin, ray.dir, vars);
		if (!hit_info.hit)
			break;
		light = col_add_col(light, col_mul_sc(color, hit_info.light));
		color = col_mul_col(color, hit_info.color);
		ray = new_ray(hit_info.poi, hit_info.normal);
		i++;
	}
	return (color_to_int(color));
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
			color = trace(vars, vars->rays[i][j], 1);
			put_pixel(vars, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
