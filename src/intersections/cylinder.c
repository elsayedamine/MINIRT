/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:18:22 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 15:52:00 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

// vecs[0] = poi
// vecs[1] = normal
void	choose_hit(t_hit hctx, t_cyl cyl, t_vec3 vecs[2], float dist)
{
	hctx.best->hit = 1;
	hctx.best->poi = vecs[0];
	hctx.best->normal = normalize(vecs[1]);
	if (dot(hctx.best->normal, cyl.dir) > 0.0f)
		hctx.best->normal = sc_op_vec(-1.0f, hctx.best->normal, mul);
	hctx.best->dist = dist;
	hctx.best->color = get_color(vecs[0], cyl.obj);
	hctx.best->obj = cyl.obj;
	hctx.best->light = 0;
	*(hctx.min_dist) = dist;
}

void	choose_solution(float racine, t_hit hctx, t_cyl cyl, float *equation)
{
	int		i;
	float	solution[2];
	float	values[2];
	t_vec3	vecs[2];

	solution[0] = (-equation[B] - racine) / (2.0f * equation[A]);
	solution[1] = (-equation[B] + racine) / (2.0f * equation[A]);
	i = -1;
	while (++i < 2)
	{
		if (solution[i] <= EPS_HIT)
			continue ;
		vecs[0] = vec_op_vec(cyl.origin, sc_op_vec(solution[i], \
			cyl.dir, mul), add);
		values[0] = dot(vec_op_vec(vecs[0], cyl.base, sub), cyl.axis);
		if (values[0] <= EPSILON || values[0] >= cyl.obj->h - EPSILON)
			continue ;
		values[1] = distance(vecs[0], cyl.origin);
		if (values[1] >= *(hctx.min_dist))
			continue ;
		vecs[1] = vec_op_vec(vec_op_vec(vecs[0], cyl.base, sub), \
			sc_op_vec(dot(vec_op_vec(vecs[0], cyl.base, sub), \
				cyl.axis), cyl.axis, mul), sub);
		choose_hit(hctx, cyl, vecs, values[1]);
	}
}

void	hit_cylinder_side(t_hit hctx, t_cyl cyl)
{
	t_vec3	vecs[3];
	float	equation[4];
	float	racine;

	vecs[0] = vec_op_vec(cyl.origin, cyl.base, sub);
	vecs[1] = vec_op_vec(cyl.dir, sc_op_vec(dot(cyl.dir, \
		cyl.axis), cyl.axis, mul), sub);
	vecs[2] = vec_op_vec(vecs[0], sc_op_vec(dot(vecs[0], \
		cyl.axis), cyl.axis, mul), sub);
	equation[A] = dot(vecs[1], vecs[1]);
	if (equation[A] <= EPSILON)
		return ;
	equation[B] = 2.0f * dot(vecs[1], vecs[2]);
	equation[C] = dot(vecs[2], vecs[2]) - (cyl.obj->r * cyl.obj->r);
	equation[DELTA] = equation[B] * equation[B] - 4 * equation[A] * equation[C];
	if (equation[DELTA] < 0.0f)
		return ;
	racine = sqrtf(fmaxf(equation[DELTA], 0.0f));
	choose_solution(racine, hctx, cyl, equation);
}

void	hit_cap(t_hit hctx, t_cyl cyl, t_vec3 center, int flip_normal)
{
	float	denom;
	float	x;
	float	dist;
	t_vec3	vecs[2];

	denom = dot(cyl.dir, cyl.axis);
	if (fabsf(denom) <= EPSILON)
		return ;
	x = dot(vec_op_vec(center, cyl.origin, sub), cyl.axis) / denom;
	if (x <= EPS_HIT)
		return ;
	vecs[0] = vec_op_vec(cyl.origin, sc_op_vec(x, cyl.dir, mul), add);
	if (distance(vecs[0], center) > cyl.obj->r + EPSILON)
		return ;
	dist = distance(vecs[0], cyl.origin);
	if (dist >= *(hctx.min_dist))
		return ;
	if (flip_normal)
		vecs[1] = sc_op_vec(-1.0f, cyl.axis, mul);
	else
		vecs[1] = cyl.axis;
	choose_hit(hctx, cyl, vecs, dist);
}

// vecs[0] = axis;
// vecs[1] = base;
// vecs[2] = top;
t_hit_info	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	float		min_dist;
	t_vec3		vecs[3];
	t_hit_info	best;
	t_cyl		cyl;
	t_hit		hctx;

	min_dist = 1e30f;
	best.hit = 0;
	vecs[0] = normalize(obj->o);
	vecs[1] = obj->p;
	vecs[2] = vec_op_vec(vecs[1], sc_op_vec(obj->h, vecs[0], mul), add);
	cyl.obj = obj;
	cyl.origin = origin;
	cyl.dir = dir;
	cyl.axis = vecs[0];
	cyl.base = vecs[1];
	hctx.best = &best;
	hctx.min_dist = &min_dist;
	hit_cylinder_side(hctx, cyl);
	hit_cap(hctx, cyl, vecs[2], 0);
	hit_cap(hctx, cyl, vecs[1], 1);
	return (best);
}
