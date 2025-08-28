/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:31:58 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/27 20:39:13 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info	intersect_rectangle(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	t_vec3		u[2];
	t_vec3		axis;
	t_vec3		vec;
	float		x[2];

	hit = intersect_plane(origin, dir, obj);
	if (!hit.hit)
		return (hit);
	if (fabs(obj->n.x) > 0.9f)
		axis = (t_vec3){0, 1, 0};
	else
		axis = (t_vec3){1, 0, 0};
	u[0] = normalize(cross(axis, obj->n));
	u[1] = cross(obj->n, u[0]);
	vec = vec_op_vec(hit.poi, obj->p, sub);
	x[0] = dot(vec, u[0]);
	x[1] = dot(vec, u[1]);
	if (fabs(x[0]) > obj->w / 2.0f || fabs(x[1]) > obj->h / 2.0f)
		hit.hit = 0;
	return (hit);
}
