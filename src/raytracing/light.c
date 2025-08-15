/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:41:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:41:08 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	t_vec3		oc;
	float		x1, x2, x;
	float		radius = 5;

	hit.hit = 0;	
	hit.light = 0;
	oc = vec_op_vec(origin, obj->p, sub);
	float a = dot(dir, dir);
	float b = 2 * dot(oc, dir);
	float c = dot(oc, oc) - radius * radius;
	float delta = b * b - 4 * a * c;
	hit.dist = 0;
	if (delta < 0)
		return (hit.hit = 0, hit);
	x1 = (-b - sqrtf(delta)) / (2 * a);
	x2 = (-b + sqrtf(delta)) / (2 * a);
	if (x1 > 0)
		x = x1;
	else if (x2 > 0)
		x = x2;
	else
		return (hit.hit = 0, hit);
	hit.hit = 1;
	hit.dist = distance(hit.poi, origin);
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.normal = normalize(vec_op_vec(hit.poi, obj->p, sub));
	hit.color = obj->t.c1;
	hit.light = obj->ratio;
	hit.obj = obj;
	return (hit);
}
