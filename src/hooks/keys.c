/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/08 19:21:25 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void translation(t_minirt *vars, int c)
{
	t_vec3 trans;

	trans = init_vec((c == 'a') - (c == 'd'),
		(c == 'w') - (c == 's'), (c == 'q') - (c == 'e'));
	vars->selected->p = vec_op_vec(vars->selected->p, trans, add);
	raytracing(vars);
}

void rotation(t_minirt *vars, int c)
{
	vars->selected->p = rotate_x(vars->selected->p, ((c == 'a') - (c == 'd')) * 3);
	vars->selected->p = rotate_y(vars->selected->p, ((c == 'w') - (c == 's')) * 3);
	vars->selected->p = rotate_z(vars->selected->p, ((c == 'q') - (c == 'e')) * 3);
	raytracing(vars);
}

int keyhook(int key, t_minirt *vars)
{
	if (key == 65307)
		quit(vars);
	if (ft_strchr("wasdqe", key) && vars->selected == 1)
		translation(vars, key);
	if (ft_strchr("wasdqe", key) && vars->selected == 2)
		rotation(vars, key);
    return (TRUE);
}

int mouse_