#include <miniRT.h>

void setup_cam(t_minirt *vars)
{
	t_vec3 wup;

	wup = init_vec(0, 0, 1);
	vars->cam.rt = normalize(cross(vars->cam.fw, wup));
	vars->cam.up = normalize(cross(vars->cam.rt, vars->cam.fw));
}

t_ray calc_ray(float u, int y, t_minirt *vars)
{
	t_ray ray;
	float v;
	t_vec3 dir;
	t_vec3 offsetx;
	t_vec3 offsety;

	v = 1 - ((((float)y + .5) / M_HEIGHT) * 2);
	offsetx = sc_op_vec(u * (vars->plane_w / 2), vars->cam.rt, mul);
	offsety = sc_op_vec(v * (vars->plane_h / 2), vars->cam.up, mul);
	dir = vec_op_vec(vars->cam.crd, vars->cam.fw, add);
	dir = vec_op_vec(dir, offsetx, add);
	dir = vec_op_vec(dir, offsety, add);
	dir = vec_op_vec(dir, vars->cam.crd, sub);
	ray.origin = vars->cam.crd;
	ray.dir = normalize(dir);
	return (ray);
}

void setup_rays(t_minirt *vars)
{
	float u;
	int i;
	int j;

	i = 0;
	j = 0;
	vars->plane_w = 2 * tan((vars->cam.fov * RAD) / 2);
	vars->plane_h = vars->plane_w * (float)M_HEIGHT / (float)M_WIDTH;
	vars->rays = malloc(sizeof(t_ray *) * M_WIDTH);
	while (i < M_WIDTH)
	{
		u = (((i + .5) / M_WIDTH) * 2) - 1;
		vars->rays[i] = malloc(sizeof(t_ray) * M_HEIGHT);
		j = 0;
		while (j < M_HEIGHT)
		{
			vars->rays[i][j] = calc_ray(u, j, vars);
			j++;
		}
		i++;
	}
}

void setup(t_minirt *vars)
{
	setup_cam(vars);
	setup_rays(vars);
	init_window(vars);
}
