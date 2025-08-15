/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/15 23:11:31 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	translation(t_minirt *vars, int c)
{
	t_vec3	trans;

	trans = (t_vec3){(c == 'd') - (c == 'a') / 2.0f,
		(c == 'w') - (c == 's') / 2.0f, (c == 'q') - (c == 'e') / 2.0f};
	vars->selected.obj->p = vec_op_vec(vars->selected.obj->p, trans, add);
	raytracing(vars);
}

void	rotation(t_minirt *vars, int c)
{
	t_object	*s;
	t_vec3		rot;
	t_vec3		temp;

	rot.x = ((c == 's') - (c == 'w')) / 10.0f;
	rot.z = ((c == 'a') - (c == 'd')) / 10.0f;
	rot.y = ((c == 'e') - (c == 'q')) / 10.0f;
	s = vars->selected.obj;
	temp = vec_op_vec(sc_op_vec(s->h * 0.5f, s->o, mul), s->p, add);
	if (s->class == PLANE)
		rotate(&s->n, rot);
	else
		rotate(&s->o, rot);
	rotate(&s->tan, rot);
	rotate(&s->bitan, rot);
	if (s->class == 4 || s->class == 6)
		s->p = vec_op_vec(sc_op_vec(s->h * -0.5f, s->o, mul), temp, add);
	raytracing(vars);
}

// we must to protect the resize
void	resize(t_minirt *vars)
{
	float	scale;

	scale = ((vars->selected.mouse == 4) - (vars->selected.mouse == 5)) / 2.0f;
	if (vars->selected.obj->class == SPHERE)
		if (vars->selected.obj->r + scale > 0)
			vars->selected.obj->r += scale;
	if (vars->selected.obj->class == CYLINDER)
	{
		vars->selected.obj->h += scale;
		vars->selected.obj->r += scale;
	}
	if (vars->selected.obj->class == CONE)
	{
		vars->selected.obj->h += scale;
		vars->selected.obj->angle += scale;
	}
	raytracing(vars);
}

void	shininess(t_minirt *vars, int key)
{
	int	delta;

	if (vars->selected.obj->shininess > 100)
		delta = 10 * ((key == '-') - (key == '='));
	else if (vars->selected.obj->shininess > 10)
		delta = ((key == '-') - (key == '=')) * 10;
	else
		delta = ((key == '-') - (key == '='));
	vars->selected.obj->shininess += delta;
	if (vars->selected.obj->shininess < 1)
		return (vars->selected.obj->shininess = 1, (void)delta);
	if (vars->selected.obj->shininess > 1000000000.0f)
		return (vars->selected.obj->shininess = 1000000000.0f, (void)delta);
	raytracing(vars);
}
