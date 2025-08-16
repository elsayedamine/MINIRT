/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:21:14 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 18:55:30 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	set_hit_info(t_hit_info *hit, t_vec3 *vec, t_object *obj, t_vec3 origin)
{
	hit->poi = vec[0];
	hit->normal = vec[1];
	hit->dist = distance(vec[0], origin);
	hit->color = get_color(vec[0], obj);
	hit->obj = obj;
	hit->light = 0;
	hit->hit = 1;
}

float	cone_root(t_ray ray, t_object *obj, t_vec3 axis, t_vec3 co)
{
	float	equation[5];
	float	x[3];
	float	da;
	float	oa;
	float	cos2;

	cos2 = (obj->h * obj->h > 0.0f) * (obj->h * obj->h / \
		(obj->h * obj->h + obj->r * obj->r)) + 0.0f;
	da = dot(ray.dir, axis);
	oa = dot(co, axis);
	equation[A] = da * da - cos2 * dot(ray.dir, ray.dir);
	equation[B] = 2.0f * (oa * da - cos2 * dot(ray.dir, co));
	equation[C] = oa * oa - cos2 * dot(co, co);
	equation[DELTA] = equation[B] * equation[B] - 4.0f
		* equation[A] * equation[C];
	if (equation[DELTA] < 0.0f || fabsf(equation[A]) <= EPSILON)
		return (-1);
	equation[SQRT] = sqrtf(fmaxf(equation[DELTA], 0.0f));
	x[1] = (-equation[B] - equation[SQRT]) / (2.0f * equation[A]);
	x[2] = (-equation[B] + equation[SQRT]) / (2.0f * equation[A]);
	if (x[1] > EPSILON && (x[1] < x[2] || x[2] <= EPSILON))
		return (x[1]);
	else if (x[2] > EPSILON)
		return (x[2]);
	return (-1);
}

int	side_intersection(t_ray ray, t_object *obj, t_hit_info *best, float *b)
{
	t_vec3	axis;
	t_vec3	p;
	t_vec3	n;
	float	x[2];

	axis = normalize(obj->o);
	x[0] = cone_root(ray, obj, axis, vec_op_vec(ray.origin, obj->p, sub));
	if (x[0] < 0)
		return (0);
	p = vec_op_vec(ray.origin, sc_op_vec(x[0], ray.dir, mul), add);
	x[1] = dot(vec_op_vec(p, obj->p, sub), axis);
	if (x[1] < 0.0f || x[1] > obj->h)
		return (0);
	if (x[0] < *b)
	{
		*b = x[0];
		n = vec_op_vec(sc_op_vec(dot(vec_op_vec(p, obj->p, sub), axis), \
			axis, mul), sc_op_vec(obj->h * obj->h / (obj->h * obj->h + \
				obj->r * obj->r), vec_op_vec(p, obj->p, sub), mul), sub);
		if (magnitude(n) < EPSILON)
			n = axis;
		*best = (t_hit_info){.poi = p, .normal = normalize(n)};
	}
	return (1);
}

int	base_intersection(t_ray ray, t_object *obj, t_hit_info *best, float *b)
{
	t_vec3		base;
	t_vec3		p;
	t_vec3		diff;
	t_vec3		axis;
	float		cap;

	axis = normalize(obj->o);
	base = vec_op_vec(obj->p, sc_op_vec(obj->h, axis, mul), add);
	if (fabsf(dot(ray.dir, axis)) <= EPSILON)
		return (0);
	cap = dot(vec_op_vec(base, ray.origin, sub), axis) / dot(ray.dir, axis);
	if (cap <= EPSILON)
		return (0);
	p = vec_op_vec(ray.origin, sc_op_vec(cap, ray.dir, mul), add);
	diff = vec_op_vec(p, base, sub);
	if (dot(diff, diff) > obj->r * obj->r + EPSILON || cap >= *b + EPSILON)
		return (0);
	*b = cap;
	*best = (t_hit_info){.poi = p, .normal = axis};
	return (1);
}

t_hit_info	intersect_cone(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	float		best_t;
	t_hit_info	best;
	t_hit_info	hit;
	t_ray		ray;
	t_vec3		vec[2];

	hit.hit = 0;
	best_t = 1e30f;
	best = (t_hit_info){0};
	ray.origin = origin;
	ray.dir = dir;
	side_intersection(ray, obj, &best, &best_t);
	base_intersection(ray, obj, &best, &best_t);
	if (best_t == 1e30f)
		return (hit);
	if (dot(best.normal, dir) > 0.0f)
		best.normal = sc_op_vec(-1.0f, best.normal, mul);
	vec[0] = best.poi;
	vec[1] = best.normal;
	set_hit_info(&hit, vec, obj, origin);
	return (hit);
}
