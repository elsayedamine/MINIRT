/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/17 12:58:42 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info	get_object(t_minirt *vars, t_vec3 origin, \
	t_vec3 dir, t_intersect *f)
{
	int			i;
	t_hit_info	hit_info;
	t_hit_info	closest;

	closest.hit = 0;
	closest.dist = INFINITY;
	closest.obj = NULL;
	i = 0;
	while (vars->arr[i])
	{
		if (vars->arr[i]->class != LIGHT)
		{
			hit_info = f[vars->arr[i]->class - 3](origin, dir, vars->arr[i]);
			if (hit_info.hit && hit_info.dist > EPS_HIT && \
				hit_info.dist < closest.dist)
				closest = hit_info;
		}
		i++;
	}
	return (closest);
}

t_hit_info	get_hit_info(t_vec3 origin, t_vec3 dir, t_minirt *vars)
{
	static t_intersect	f[] = {
		intersect_sphere,
		intersect_cylinder,
		intersect_plane,
		intersect_cone,
	};

	return (get_object(vars, origin, dir, f));
}

int	is_shaded(t_minirt *vars, t_hit_info hit, t_object *light)
{
	t_vec3		light_dir;
	t_ray		shadow_ray;
	float		dist;
	t_hit_info	shadow_hit;

	light_dir = normalize(vec_op_vec(light->p, hit.poi, sub));
	shadow_ray.origin = vec_op_vec(hit.poi, sc_op_vec(EPSILON, \
		hit.normal, mul), add);
	shadow_ray.dir = light_dir;
	dist = distance(light->p, shadow_ray.origin);
	shadow_hit = get_hit_info(shadow_ray.origin, shadow_ray.dir, vars);
	if (shadow_hit.hit && shadow_hit.obj != hit.obj && shadow_hit.dist < dist)
		return (TRUE);
	return (FALSE);
}

t_color	compute_lighting(t_hit_info hit, t_object *light, t_ray ray)
{
	t_vec3	light_dir;
	t_vec3	vect;
	t_vec3	r;
	float	dotrv;
	float	dotnl;

	vect = normalize(vec_op_vec(ray.origin, hit.poi, sub));
	light_dir = normalize(vec_op_vec(light->p, hit.poi, sub));
	dotnl = fmaxf(0.0f, dot(hit.normal, light_dir));
	r = vec_op_vec(sc_op_vec(-1, light_dir, mul), \
		sc_op_vec(2 * dotnl, hit.normal, mul), add);
	dotnl = (dotnl < 0) * 0 + (dotnl >= 0) * dotnl;
	dotrv = fmaxf(0.0f, dot(r, vect));
	dotrv = (dotrv < 0) * 0 + (dotrv >= 0) * dotrv;
	return (col_add_col(
			col_mul_col(col_mul_sc(light->t.c1, dotnl), hit.color),
			col_mul_sc(light->t.c1, powf(dotrv, hit.obj->shininess))
		));
}
