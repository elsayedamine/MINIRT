/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:48:10 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:51:09 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	trace(t_minirt *vars, t_ray ray)
{
	t_hit_info	hit;
	t_color		final_color;
	t_list		*curr;
	t_object	*obj;

	hit = get_hit_info(ray.origin, ray.dir, vars);
	if (!hit.hit)
		return (0);
	final_color = col_mul_col(hit.color, \
		col_mul_sc(vars->amb_rgb, vars->amb_ratio));
	curr = vars->members;
	while (curr)
	{
		obj = (t_object *)curr->content;
		if (obj->class == LIGHT && !is_shadowed(vars, hit, obj))
			final_color = col_add_col(final_color, \
				compute_lighting(hit, obj, ray));
		curr = curr->next;
	}
	return (color_to_int(final_color));
}

void	trace_vertical(void *args)
{
	t_minirt	*vars;
	void		**new_args;
	int			color;
	int			i;
	int			j;

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

void	raytracing(t_minirt *vars)
{
	void	*args;
	t_pool	pool;
	int		i;

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
