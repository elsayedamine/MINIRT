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
		intersect_plane,
		intersect_cone,
	};

	curr = vars->members;
	closest.hit = 0;
	closest.dist = INFINITY;
	closest.obj = NULL;
	while (curr)
	{
		obj = (t_object *)curr->content;
		if (obj->class == LIGHT)
		{
			curr = curr->next;
			continue ;
		}
		hit_info = f[obj->class - 2](origin, dir, obj);
		if (hit_info.hit && hit_info.dist > EPS_HIT && hit_info.dist < closest.dist)
    		closest = hit_info;
		curr = curr->next;
	}
	return (closest);
}

int is_shadowed(t_minirt *vars, t_hit_info hit, t_object *light)
{
	t_vec3 light_dir = normalize(vec_op_vec(light->p, hit.poi, sub));
	t_ray shadow_ray;
	shadow_ray.origin = vec_op_vec(hit.poi, sc_op_vec(EPSILON, hit.normal, mul), add);
	shadow_ray.dir = light_dir;
	float dist = distance(light->p, hit.poi);
	t_hit_info shadow_hit = get_hit_info(shadow_ray.origin, shadow_ray.dir, vars);
	if (shadow_hit.hit && shadow_hit.dist < dist)
		return TRUE;
	return FALSE;
}

t_color compute_lighting(t_minirt *vars, t_hit_info hit, t_object *light, t_ray ray)
{
	(void)vars;
	t_vec3 light_dir = normalize(vec_op_vec(light->p, hit.poi, sub));
	t_vec3 vect = normalize(vec_op_vec(ray.origin, hit.poi, sub));
	float dotNL = dot(hit.normal, light_dir);
	t_vec3 R = vec_op_vec(sc_op_vec(-1, light_dir, mul), sc_op_vec(2 * dotNL, hit.normal, mul), add);
	dotNL = (dotNL < 0) * 0 + (dotNL >= 0) * dotNL;
	float dotRV = dot(R, vect);
	dotRV = (dotRV < 0) * 0 + (dotRV >= 0) * dotRV;
	// float	dist = distance(hit.poi, light->p);
	t_color diffuse = col_mul_sc(light->t.c1, dotNL);
	float shininess = 100.0f; // this line literally controls the shininess 
	t_color specular = col_mul_sc(light->t.c1, powf(dotRV, shininess));
	t_color final = col_add_col(col_mul_col(diffuse, hit.color), specular);
	return (final);
}

int	trace(t_minirt *vars, t_ray ray)
{
	t_hit_info	hit;
	t_color		final_color;

	hit = get_hit_info(ray.origin, ray.dir, vars);
	if (!hit.hit)
		return (0);
	final_color = col_mul_col(hit.color, col_mul_sc(vars->amb_rgb, vars->amb_ratio));
	t_list *curr = vars->members;
	while (curr)
	{
		t_object *obj = (t_object *)curr->content;
		if (obj->class == LIGHT && !is_shadowed(vars, hit, obj))
			final_color = col_add_col(final_color, compute_lighting(vars, hit, obj, ray));
		curr = curr->next;
	}
	return (color_to_int(final_color));
}

void trace_vertical(void *args)
{
	void **new_args;
	t_minirt *vars;
	int color;
	int i;
	int j;

	new_args = (void **)args;
	vars = (t_minirt *)(new_args[0]);
	i = *(int *)(new_args[1]);
	j = -1;
	while (++j < M_HEIGHT)
	{
		color = trace(vars, vars->rays[i][j]);
		put_pixel(vars, i, j, color);
	}
}

void raytracing(t_minirt *vars)
{
	void *args;
	t_pool pool;
	int i;

	init_pool(&pool);
	i = -1;
	while (++i < M_WIDTH)
	{
		args = mk_args(2, vars, sizeof(t_minirt), &i, 4);
		add_task(&pool, trace_vertical, args);
	}
	pool_wait(&pool);
	pool_destroy(&pool);
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
