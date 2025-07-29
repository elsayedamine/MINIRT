#include <miniRT.h>

void	put_pixel(t_minirt *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < M_WIDTH && y >= 0 && y < M_HEIGHT)
	{
		dst = vars->win.addr + (y * vars->win.line_length + x * (vars->win.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
