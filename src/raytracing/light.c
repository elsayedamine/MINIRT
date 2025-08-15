/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:41:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 23:43:01 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info	fill_hit_light(t_vec3 origin, t_vec3 dir, t_object *obj, float x)
{
	t_hit_info	hit;

	hit.hit = 1;
	hit.dist = distance(hit.poi, origin);
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.normal = normalize(vec_op_vec(hit.poi, obj->p, sub));
	hit.color = obj->t.c1;
	hit.light = obj->ratio;
	hit.obj = obj;
	return (hit);
}

t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	t_vec3		oc;
	float		x[3];
	float		radius;
	float		equation[4];

	radius = 5;
	hit.hit = 0;
	hit.dist = 0;
	oc = vec_op_vec(origin, obj->p, sub);
	equation[A] = dot(dir, dir);
	equation[B] = 2 * dot(oc, dir);
	equation[C] = dot(oc, oc) - radius * radius;
	equation[DELTA] = equation[B] * equation[B] - 4 * equation[A] * equation[C];
	if (equation[DELTA] < 0)
		return (hit.hit = 0, hit);
	x[1] = (-equation[B] - sqrtf(equation[DELTA])) / (2 * equation[A]);
	x[2] = (-equation[B] + sqrtf(equation[DELTA])) / (2 * equation[A]);
	if (x[1] > 0)
		x[0] = x[1];
	else if (x[2] > 0)
		x[0] = x[2];
	else
		return (hit.hit = 0, hit);
	return (fill_hit_light(origin, dir, obj, x[0]));
}
