#include <miniRT.h>

void setup_cam(t_camera *cam)
{
	t_vec3 wup;

	wup = init_vec(0, 0, 1);
	cam->rt = normalize(cross(cam->fw, wup));
	cam->up = normalize(cross(cam->rt, cam->fw));
}

t_vec3 calc_ray(int x, int y, t_projection plane, t_camera cam)
{
	float u;
	float v;
	t_vec3 dir;
	t_vec3 offsetx;
	t_vec3 offsety;

	u = ((x + .5) / M_WIDTH) * 2 - 1;
	v = 1 - ((y + .5) / M_HEIGHT) * 2;
	offsetx = sc_op_vec(u * (plane.projection_plane_w / 2), cam.rt, mul);
	offsety = sc_op_vec(v * (plane.projection_plane_h / 2), cam.up, mul);
	dir = vec_op_vec(cam.crd, cam.fw, add);
	dir = vec_op_vec(dir, offsetx, add);
	dir = vec_op_vec(dir, offsety, add);
	dir = vec_op_vec(dir, cam.crd, sub);
	return (normalize(dir));
}

void setup_rays(t_projection *plane, t_camera cam)
{
	int i;
	int j;

	i = 0;
	j = 0;
	plane->projection_plane_w = 2 * tan(cam.fov * RAD / 2);
	plane->projection_plane_h = plane->projection_plane_w * M_HEIGHT / M_WIDTH;
	plane->rays = malloc(sizeof(t_vec3 *) * M_WIDTH);
	while (i < M_WIDTH)
	{
		plane->rays[i] = malloc(sizeof(t_vec3) * M_HEIGHT);
		while (j < M_HEIGHT)
		{
			plane->rays[i][j] = calc_ray(i, j, *plane, cam);
			j++;
		}
		i++;
	}
}

void setup(t_minirt *vars)
{
	setup_cam(&vars->cam);
	setup_rays(&vars->plane, vars->cam);
}