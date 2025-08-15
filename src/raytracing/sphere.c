/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:53 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:41:48 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *obj)
{
    t_hit_info hit;
    float a = dot(dir, dir);
    t_vec3 oc = vec_op_vec(origin, obj->p, sub);
    float b = 2 * dot(oc, dir);
    float c = dot(oc, oc) - obj->r * obj->r;
    float delta = b * b - 4 * a * c;

    if (delta < 0.0f)
        return (hit.hit = 0, hit);
    float sqrt_delta = sqrtf(fmaxf(delta, 0.0f));
    float x1 = (-b - sqrt_delta) / (2 * a);
    float x2 = (-b + sqrt_delta) / (2 * a);
    float x = 0;
    if (x1 > EPS_HIT && (x1 < x2 || x2 <= EPS_HIT))
        x = x1;
    else if (x2 > EPS_HIT)
        x = x2;
    else
        return (hit.hit = 0, hit);
    hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
    hit.normal = normalize(vec_op_vec(hit.poi, obj->p, sub));
    if (dot(hit.normal, dir) > 0)
        hit.normal = sc_op_vec(-1, hit.normal, mul);
    hit.dist = distance(hit.poi, origin);
    hit.color = get_color(hit.poi, obj);
    hit.obj = obj;
    hit.light = 0;
    hit.hit = 1;
    return (hit);
}
