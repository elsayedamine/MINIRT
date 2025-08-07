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

	curr = vars->members;
	closest.hit = 0;
	closest.dist = INFINITY;
	while (curr)
	{
		obj = (t_object *)curr->content;
		if (obj->class == LIGHT)
		{
			curr = curr->next;
			continue ;
		}
		hit_info = f[obj->class - 2](origin, dir, obj);
		if (hit_info.hit && hit_info.dist < closest.dist)
			closest = hit_info;
		curr = curr->next;
	}
	return (closest);
}

int is_shadowed(t_minirt *vars, t_hit_info hit, t_object *light)
{
    t_vec3 light_dir = normalize(vec_op_vec(light->crd, hit.poi, sub));
    t_ray shadow_ray;
    shadow_ray.origin = vec_op_vec(hit.poi, sc_op_vec(EPSILON, light_dir, mul), add);
    shadow_ray.dir = light_dir;
    float dist = distance(light->crd, hit.poi);
    t_hit_info shadow_hit = get_hit_info(shadow_ray.origin, shadow_ray.dir, vars);
    if (shadow_hit.hit && shadow_hit.dist < dist)
        return TRUE;
    return FALSE;
}

t_color compute_lighting(t_minirt *vars, t_hit_info hit, t_object *light, t_ray ray)
{
    t_vec3 light_dir = normalize(vec_op_vec(light->crd, hit.poi, sub));
    t_vec3 vect = normalize(vec_op_vec(ray.origin, hit.poi, sub));
    float dotNL = dot(hit.normal, light_dir);
    t_vec3 R = vec_op_vec(sc_op_vec(-1, light_dir, mul), sc_op_vec(2 * dotNL, hit.normal, mul), add);
    if (dotNL < 0)
        dotNL = 0;
    float dotRV = dot(R, vect);
    if (dotRV < 0)
        dotRV = 0;
    t_color diffuse = col_mul_sc(light->rgb, dotNL);
    float shininess = 32.0f;
    t_color specular = col_mul_sc(light->rgb, powf(dotRV, shininess));
    t_color final = col_mul_col(col_add_col(diffuse, specular), hit.color);
    return final;
}

t_color trace(t_minirt *vars, t_ray ray)
{
	t_hit_info hit;
	t_color final_color;
	t_color light_component;

	hit = get_hit_info(ray.origin, ray.dir, vars);
	if (!hit.hit)
		return (init_color(0, 0, 0));
	final_color = col_mul_col(hit.color, col_mul_sc(vars->amb_rgb, vars->amb_ratio));
	t_list *curr = vars->members;
	while (curr)
	{
	    t_object *obj = (t_object *)curr->content;
	    if (obj->class == LIGHT)
	    {
	        if (!is_shadowed(vars, hit, obj))
	        {
	            light_component = compute_lighting(vars, hit, obj, ray);
	            final_color = col_add_col(final_color, light_component);
	        }
	    }
	    curr = curr->next;
	}
    return (col_add_col(final_color, (t_color){0, 0, 0}));
}

void raytracing(t_minirt *vars)
{
	int i, j, color;

	i = -1;
	while (++i < M_WIDTH)
	{
		j = -1;
		while (++j < M_HEIGHT)
		{
			color = color_to_int(trace(vars, vars->rays[i][j]));
			put_pixel(vars, i, j, color);
		}
	}
	puts("done");
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
