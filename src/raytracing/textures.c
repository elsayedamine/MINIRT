/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:30:34 by sayed             #+#    #+#             */
/*   Updated: 2025/08/15 23:29:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_vec3	get_uv_cone(t_vec3 poi, t_object *obj)
{
	t_vec3	local;
	t_vec3	uv;
	t_vec3	rel;

	rel = vec_op_vec(poi, obj->p, sub);
	local.x = dot(rel, obj->tan);
	local.y = dot(rel, obj->o);
	local.z = dot(rel, obj->bitan);
	uv.x = obj->facing + atan2(local.z, local.x) / (2.0f * M_PI);
	if (uv.x < 0.0f)
		uv.x += 1.0f;
	uv.y = 1.0f - local.y / obj->h;
	return (uv);
}

t_vec3	get_uv_cylinder(t_vec3 poi, t_object *obj)
{
	t_vec3	local;
	t_vec3	uv;
	t_vec3	rel;

	rel = vec_op_vec(poi, obj->p, sub);
	local.x = dot(rel, obj->tan);
	local.y = dot(rel, obj->o);
	local.z = dot(rel, obj->bitan);
	uv.x = obj->facing + atan2(local.z, local.x) / (2.0f * M_PI);
	if (uv.x < 0.0f)
		uv.x += 1.0f;
	uv.y = 1.0f - local.y / obj->h;
	return (uv);
}

t_vec3	get_uv_plane(t_vec3 poi, t_object *obj)
{
	t_vec3	local;
	t_vec3	uv;

	local = vec_op_vec(poi, obj->p, sub);
	uv.x = dot(local, obj->tan) * obj->ratio;
	uv.y = dot(local, obj->bitan) * obj->ratio;
	uv.x = uv.x - floorf(uv.x);
	uv.y = uv.y - floorf(uv.y);
	return (uv);
}

t_vec3	get_uv_sphere(t_vec3 poi, t_object *obj)
{
	t_vec3	local;
	t_vec3	uv;
	t_vec3	rel;

	rel = vec_op_vec(poi, obj->p, sub);
	local.x = dot(rel, obj->tan);
	local.y = dot(rel, obj->o);
	local.z = dot(rel, obj->bitan);
	local = sc_op_vec(1.0f / obj->r, local, mul);
	uv.x = obj->facing + atan2(local.z, local.x) / (2.0f * M_PI);
	uv.y = acos(local.y) / M_PI;
	return (uv);
}
