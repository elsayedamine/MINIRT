#include <miniRT.h>

void    hook_manipulation(t_minirt *vars)
{
	mlx_key_hook(vars->win.win, keyhook, vars);
	mlx_hook(vars->win.win, 17, 1L << 0, quit, vars);
	mlx_loop(vars->win.mlx);
}
