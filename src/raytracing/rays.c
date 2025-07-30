#include <miniRT.h>

t_hit_info get_hit_info(t_vec3 origin, t_vec3 dir, t_minirt *vars)
{
	t_list				*curr;
	t_object			*obj;
	t_hit_info			hit_info;
	t_hit_info			closest;
	static t_intersect	f[] = {
		intersect_light,
		intersect_sphere,
		intersect_cylinder,
		intersect_plan,
		intersect_last_shape,
	};

	curr = vars->members->next;
	closest.hit = 0;
	closest.dist = INFINITY;
	while (curr)
	{
		obj = (t_object *)curr->content;
		hit_info = f[obj->class - 2](origin, dir, obj);
		if (hit_info.hit && hit_info.dist < closest.dist)
			closest = hit_info;
		curr = curr->next;
	}
	return (closest);
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

float	compute_light(t_hit_info *hit, t_minirt *vars)
{
	// t_vec3	shadow_dir;
	t_object	*light;

	light = (t_object *)vars->members->next->next;
	if (!light)
		return (0.0f);
	t_vec3 shadow_dir = normalize(vec_op_vec(light->crd, hit->poi, sub));
	t_vec3 shadow_origin = vec_op_vec(hit->poi, sc_op_vec(EPSILON, hit->normal, add), add);
	t_hit_info hit_light = get_hit_info(shadow_origin, shadow_dir, vars);
	float dist_to_light = magnitude(vec_op_vec(light->crd, hit->poi, sub));

	if (hit_light.hit == 1 && hit_light.dist < dist_to_light)
		return (0.0f);
	float light_intensity = light->ratio * fmax(0, dot(hit->normal, shadow_dir));
	return (light_intensity);
}

int    trace(t_minirt *vars, t_ray ray, int count)
{
    t_color light;
    t_color color;
    t_hit_info hit_info;
    int i;

    i = 0;
    light = init_color(0, 0, 0);
    // light = col_mul_sc(init_color(255, 255, 255), vars->amb_ratio);
    color = init_color(255, 255, 255);
    while (i < count)
    {
        hit_info = get_hit_info(ray.origin, ray.dir, vars);
        if (!hit_info.hit)
            break;
        // hit_info.light = compute_light(&hit_info, vars);
        // light = col_mul_col(light, vars->amb_rgb);
        light = col_add_col(light, col_mul_sc(color, hit_info.light));
        // printf()
        color = col_mul_col(color, hit_info.color);
        ray = new_ray(hit_info.poi, hit_info.normal);
        i++;
    }
    return (color_to_int(light));
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
			color = trace(vars, vars->rays[i][j], 50);
			put_pixel(vars, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
