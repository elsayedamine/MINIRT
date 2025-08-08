#include <miniRT.h>

void setup_cam(t_minirt *vars)
{
	t_vec3 wup;

	if (fabs(vars->cam.fw.x) == 0 && fabs(vars->cam.fw.y) == 0)
		wup = init_vec(0, 1, 0); // use Y axis if fw is colinear with Z
	else
		wup = init_vec(0, 0, 1);
	vars->cam.rt = normalize(cross(vars->cam.fw, wup));
	vars->cam.up = normalize(cross(vars->cam.rt, vars->cam.fw));
}

t_ray calc_ray(float u, int y, t_minirt *vars, float plane[2])
{
	float v;
	t_ray ray;
	t_vec3 offsetx;
	t_vec3 offsety;

	v = 1 - ((((float)y + .5) / M_HEIGHT) * 2);
	offsetx = sc_op_vec(u * (plane[W] / 2), vars->cam.rt, mul);
	offsety = sc_op_vec(v * (plane[H] / 2), vars->cam.up, mul);
	ray.dir = vec_op_vec(vars->cam.p, vars->cam.fw, add);
	ray.dir = vec_op_vec(ray.dir, offsetx, add);
	ray.dir = vec_op_vec(ray.dir, offsety, add);
	ray.dir = vec_op_vec(ray.dir, vars->cam.p, sub);
	ray.dir = normalize(ray.dir);
	ray.origin = vars->cam.p;
	return (ray);
}

t_ray	**setup_rays(t_minirt *vars)
{
	float u;
	int i;
	int j;
	float	plane[2];
	t_ray	**rays;

	i = 0;
	j = 0;
	plane[W] = 2 * tan((vars->cam.fov * RAD) / 2);
	plane[H] = plane[W] * (float)M_HEIGHT / (float)M_WIDTH;
	rays = malloc(sizeof(t_ray *) * M_WIDTH);
	while (i < M_WIDTH)
	{
		u = (((i + .5) / M_WIDTH) * 2) - 1;
		rays[i] = malloc(sizeof(t_ray) * M_HEIGHT);
		j = -1;
		while (++j < M_HEIGHT)
			rays[i][j] = calc_ray(u, j, vars, plane);
		i++;
	}
	return (rays);
}

t_ray	**setup(t_minirt *vars)
{
	setup_cam(vars);
	return (setup_rays(vars));
}
