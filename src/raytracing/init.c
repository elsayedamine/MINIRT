#include <miniRT.h>

void setup_cam(t_minirt *vars, int cam_id)
{
	t_vec3 wup;

	if (fabs(vars->cam[cam_id].fw.x) == 0 && fabs(vars->cam[cam_id].fw.y) == 0)
		wup = (t_vec3){0, 1, 0}; // use Y axis if fw is colinear with Z
	else
		wup = (t_vec3){0, 0, 1};
	vars->cam[cam_id].rt = normalize(cross(vars->cam[cam_id].fw, wup));
	vars->cam[cam_id].up = normalize(cross(vars->cam[cam_id].rt, vars->cam[cam_id].fw));
}

t_ray calc_ray(float u, int y, t_minirt *vars, int cam_id)
{
	t_ray ray;
	float v;
	t_vec3 offsetx;
	t_vec3 offsety;

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

void setup_rays(t_minirt *vars, int cam_id)
{
	float u;
	int i;
	int j;

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
			// print_vec(vars->rays[i][j].dir, 1);
			j++;
		}
		i++;
	}
}

void	setup(t_minirt *vars, int cam_id)
{
	vars->cam_id = cam_id;
	setup_cam(vars, cam_id);
	setup_rays(vars, cam_id);
}
