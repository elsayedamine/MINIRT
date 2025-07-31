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
		hit_info = f[obj->class - 2](origin, dir, obj);
		// printf("%s\n", g_strs[obj->class]);
		if (hit_info.hit && hit_info.dist < closest.dist)
			closest = hit_info;
		curr = curr->next;
	}
	return (closest);
}

t_ray new_ray(t_vec3 pos, t_vec3 normal)
{
	t_ray new;
	float x, y, z;

	x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	z = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	new.dir = init_vec(x, y, z);
	if (dot(new.dir, normal) < 0)
		new.dir = sc_op_vec(-1, new.dir, mul);
	new.dir = normalize(vec_op_vec(normalize(new.dir), normal, add));
	// print_vec(new.dir, 1);
	// new.origin = pos;
	new.origin = vec_op_vec(pos, sc_op_vec(EPSILON, normal, mul), add);
	// new.origin = vec_op_vec(pos, new.dir, add);
	return (new);
}

t_color    trace(t_minirt *vars, t_ray ray, int count)
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
		printf("%d - %d - %d\n", hit_info.color.r, hit_info.color.g, hit_info.color.b);
        if (!hit_info.hit)
            break ;
        // light = col_mul_col(light, vars->amb_rgb);
        light = col_add_col(light, col_mul_sc(color, hit_info.light));
        color = col_mul_col(color, hit_info.color);
        ray = new_ray(hit_info.poi, hit_info.normal);
    }
    return (light);
}

t_vec3 jitter_ray(t_vec3 ray_dir, float max_angle_rad)
{
	t_vec3 u, v;

	// Build an orthonormal basis (u, v, w), where w = ray_dir
	t_vec3 w = normalize(ray_dir);
	if (fabs(w.x) > 0.1)
		u = normalize(cross((t_vec3){0,1,0}, w));
	else
		u = normalize(cross((t_vec3){1,0,0}, w));
	v = cross(w, u);

	// Generate random polar coordinates within the cone
	float rand1 = (float)rand() / RAND_MAX; // ∈ [0,1)
	float rand2 = (float)rand() / RAND_MAX;
	float theta = acos(1.0 - rand1 * (1.0 - cos(max_angle_rad)));
	float phi = 2.0 * M_PI * rand2;

	float x = sin(theta) * cos(phi);
	float y = sin(theta) * sin(phi);
	float z = cos(theta);

	// Convert to world space
	t_vec3 jittered_dir = sc_op_vec(x, u, mul);
	jittered_dir = vec_op_vec(sc_op_vec(y, v, mul), jittered_dir, add);
	jittered_dir = vec_op_vec(sc_op_vec(z, w, mul), jittered_dir, add);	
	return (normalize(jittered_dir));
}

int sample(t_minirt *vars, t_ray ray, int samples)
{
	t_color color;
	int i;

	i = 0;
	// printf("-----");
	// print_vec(ray.dir, 1);
	color = init_color(0, 0, 0);
	while (i < samples)
	{
		// ray.dir = jitter_ray(ray.dir, .05);
		// print_vec(ray.dir, 1);
		color = col_add_col(color, trace(vars, ray, 10));
		i++;
	}
	return (color_to_int(col_mul_sc(color, 1.0f / samples)));
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
			color = color_to_int(trace(vars, vars->rays[i][j], 10));
			put_pixel(vars, i, j, color);
			j++;
		}
		i++;
	}
	puts("done");
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
