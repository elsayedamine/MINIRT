#include <miniRT.h>

int	trace(t_vec3 dir, t_minirt *vars)
{
	(void)vars;
	t_vec3 color = sc_op_vec(1, dir, add);
	color = sc_op_vec(.5, color, mul);
	color = sc_op_vec(255, color, mul);
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
			color = trace(vars->plane.rays[i][j], vars);
			put_pixel(vars, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->win.mlx, vars->win.win, vars->win.img, 0, 0);
}
