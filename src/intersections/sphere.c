/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:53 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 23:43:08 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info	fill_hit_sphere(t_vec3 origin, t_vec3 dir, t_object *obj, float x)
{
	t_hit_info	hit;

	hit.hit = 1;
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.normal = normalize(vec_op_vec(hit.poi, obj->p, sub));
	if (dot(hit.normal, dir) > 0)
		hit.normal = sc_op_vec(-1, hit.normal, mul);
	hit.dist = distance(hit.poi, origin);
	hit.color = get_color(hit.poi, obj);
	hit.obj = obj;
	hit.light = 0;
	return (hit);
}

t_hit_info	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	t_vec3		oc;
	float		equation[4];
	float		x[4];

	hit = (t_hit_info){.poi = (t_vec3){0.0f, 0.0f, 0.0f}, \
		.normal = (t_vec3){0, 0, 0}, .color = (t_color){0, 0, 0}, .obj = NULL};
	ft_init(3, &hit.hit, &hit.light, &hit.dist);
	oc = vec_op_vec(origin, obj->p, sub);
	equation[A] = dot(dir, dir);
	equation[B] = 2 * dot(oc, dir);
	equation[C] = dot(oc, oc) - obj->r * obj->r;
	equation[DELTA] = equation[B] * equation[B] - 4 * equation[A] * equation[C];
	if (equation[DELTA] < 0.0f)
		return (hit.hit = 0, hit);
	x[3] = sqrtf(fmaxf(equation[DELTA], 0.0f));
	x[1] = (-equation[B] - x[3]) / (2 * equation[A]);
	x[2] = (-equation[B] + x[3]) / (2 * equation[A]);
	if (x[1] > EPS_HIT && (x[1] < x[2] || x[2] <= EPS_HIT))
		x[0] = x[1];
	else if (x[2] > EPS_HIT)
		x[0] = x[2];
	else
		return (hit.hit = 0, hit);
	return (fill_hit_sphere(origin, dir, obj, x[0]));
}
