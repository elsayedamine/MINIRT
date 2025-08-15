/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:41:25 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 23:38:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	float		x;

	if (dot(obj->n, dir) == 0)
		return (hit.hit = 0, hit);
	x = (dot(obj->n, vec_op_vec(obj->p, origin, sub))) / dot(obj->n, dir);
	if (x <= 0)
		return (hit.hit = 0, hit);
	hit.hit = 1;
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.normal = obj->n;
	hit.dist = x;
	hit.color = get_color(hit.poi, obj);
	hit.light = 0;
	hit.obj = obj;
	return (hit);
}
