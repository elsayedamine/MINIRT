/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/17 14:03:36 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	translation(t_minirt *vars, int c)
{
	t_vec3	trans;
	t_vec3	new_pos;
	t_vec3	dir;
	float	dist_to_light;
	int		i;

	trans = (t_vec3){
		((c == 'd') - (c == 'a')) / 2.0f,
		((c == 'w') - (c == 's')) / 2.0f,
		((c == 'q') - (c == 'e')) / 2.0f
	};
	new_pos = vec_op_vec(vars->selected.obj->p, trans, add);
	dir = normalize(trans);
	i = -1;
	while (vars->arr[++i])
	{
		if (vars->arr[i]->class != LIGHT)
			continue ;
		dist_to_light = distance(new_pos, vars->arr[i]->p);
		if (dist_to_light < 2.5f)
			new_pos = vec_op_vec(new_pos, sc_op_vec((2.5f - \
				dist_to_light + 0.1f), dir, mul), add);
	}
	vars->selected.obj->p = new_pos;
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
	if (s->class == CYLINDER || s->class == CONE)
		s->p = vec_op_vec(sc_op_vec(s->h * -0.5f, s->o, mul), temp, add);
	raytracing(vars);
}

void	resize(t_minirt *vars)
{
	float			scale;
	t_object		*obj;
	float			max_scale;

	obj = vars->selected.obj;
	scale = ((vars->selected.mouse == 4) - (vars->selected.mouse == 5)) * 0.5f;
	if (obj->class == SPHERE && obj->r + scale > 1.0f)
		obj->r += scale;
	else if (obj->class == CYLINDER)
	{
		if (scale < 0)
			max_scale = obj->r - 1.0f;
		else
			max_scale = 1e30f;
		if (scale < -max_scale)
			scale = -max_scale;
		obj->h += scale;
		obj->r = obj->h * obj->ratio;
	}
	else if (obj->class == CONE && obj->h + scale > 1.0f)
		obj->h += scale;
	raytracing(vars);
}

void	shininess(t_minirt *vars, int key)
{
	int	delta;

	if (vars->selected.obj->shininess > 1000000)
		delta = 100 * ((key == '-') - (key == '='));
	else if (vars->selected.obj->shininess > 100)
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

void	translate_light(t_minirt *vars, int c)
{
	t_vec3	trans;
	int		i;

	trans = (t_vec3){((c == 'l') - (c == 'j')) / 2.0f,
		((c == 'i') - (c == 'k')) / 2.0f, ((c == 'u') - (c == 'o')) / 2.0f};
	i = -1;
	while (vars->arr[++i])
		if (vars->arr[i]->class == LIGHT)
			break ;
	if (!vars->arr[i])
		return ;
	vars->arr[i]->p = vec_op_vec(vars->arr[i]->p, trans, add);
	raytracing(vars);
}
