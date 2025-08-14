/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:18:22 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/14 17:19:25 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

typedef struct s_cyl
{
	t_object *obj;
	t_vec3	origin;
	t_vec3	dir;
	t_vec3	base;
	t_vec3	axis;
}	t_cyl;

typedef struct s_hit
{
	t_hit_info	*best;
	float		*min_dist;
}	t_hit;

void	choose_hit(t_hit hctx, t_cyl cyl, t_vec3 poi, t_vec3 normal, float dist)
{
	hctx.best->hit = 1;
	hctx.best->poi = poi;
	hctx.best->normal = normalize(normal);
	if (dot(hctx.best->normal, cyl.dir) > 0.0f)
		hctx.best->normal = sc_op_vec(-1.0f, hctx.best->normal, mul);
	hctx.best->dist = dist;
	hctx.best->color = get_color(poi, cyl.obj);
	hctx.best->obj = cyl.obj;
	hctx.best->light = 0;
	*(hctx.min_dist) = dist;
}

void	hit_cylinder_side(t_hit hctx, t_cyl cyl)
{
	t_vec3 w = vec_op_vec(cyl.origin, cyl.base, sub);
	float axis_dot_dir = dot(cyl.dir, cyl.axis);
	t_vec3 d_perp = vec_op_vec(cyl.dir, sc_op_vec(axis_dot_dir, cyl.axis, mul), sub);
	t_vec3 w_perp = vec_op_vec(w, sc_op_vec(dot(w, cyl.axis), cyl.axis, mul), sub);

	float a = dot(d_perp, d_perp);
	if (a <= EPSILON)
		return ;
	float b = 2.0f * dot(d_perp, w_perp);
	float c = dot(w_perp, w_perp) - (cyl.obj->r * cyl.obj->r);
	float delta = b * b - 4 * a * c;
	if (delta < 0.0f)
		return ;
	float racine = sqrtf(fmaxf(delta, 0.0f));
	float solution[2] = { (-b - racine) / (2.0f * a), (-b + racine) / (2.0f * a) };

	int i = -1;
	while (++i < 2)
	{
		if (solution[i] <= EPS_HIT)
			continue ;
		t_vec3 poi = vec_op_vec(cyl.origin, sc_op_vec(solution[i], cyl.dir, mul), add);
		float proj = dot(vec_op_vec(poi, cyl.base, sub), cyl.axis);
		if (proj <= EPSILON || proj >= cyl.obj->h - EPSILON)
			continue ;
		float dist = distance(poi, cyl.origin);
		if (dist >= *(hctx.min_dist))
			continue ;
		t_vec3 proj_v = sc_op_vec(dot(vec_op_vec(poi, cyl.base, sub), cyl.axis), cyl.axis, mul);
		t_vec3 normal = vec_op_vec(vec_op_vec(poi, cyl.base, sub), proj_v, sub);
		choose_hit(hctx, cyl, poi, normal, dist);
	}
}

void	hit_cap(t_hit hctx, t_cyl cyl,
					t_vec3 center, int flip_normal)
{
	float denom = dot(cyl.dir, cyl.axis);
	if (fabsf(denom) <= EPSILON)
		return ;
	float x = dot(vec_op_vec(center, cyl.origin, sub), cyl.axis) / denom;
	if (x <= EPS_HIT)
		return ;
	t_vec3 poi = vec_op_vec(cyl.origin, sc_op_vec(x, cyl.dir, mul), add);
	if (distance(poi, center) > cyl.obj->r + EPSILON)
		return ;
	float dist = distance(poi, cyl.origin);
	if (dist >= *(hctx.min_dist))
		return ;
	t_vec3 normal;
	if (flip_normal)
		normal = sc_op_vec(-1.0f, cyl.axis, mul);
	else
		normal = cyl.axis;
	choose_hit(hctx, cyl, poi, normal, dist);
}

t_hit_info intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	float min_dist = 1e30f;
	t_hit_info best;

	best.hit = 0;
	t_vec3 axis = normalize(obj->o);
	t_vec3 base = obj->p;
	t_vec3 top  = vec_op_vec(base, sc_op_vec(obj->h, axis, mul), add);

	t_cyl cyl = { obj, origin, dir, base, axis };
	t_hit hctx = { &best, &min_dist };

	hit_cylinder_side(hctx, cyl);
	hit_cap(hctx, cyl, top, 0);
	hit_cap(hctx, cyl, base, 1);

	return (best);
}
