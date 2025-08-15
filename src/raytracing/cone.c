/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:21:14 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 18:25:54 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_hit_info intersect_cone(t_vec3 origin, t_vec3 dir, t_object *obj)
{
    t_hit_info hit;
    hit.hit = 0;

    const float INF_DIST = 1e30f;
    const float EPS = 1e-5f; // small bias for seam and apex

    float best_t = INF_DIST;
    t_vec3 best_poi = (t_vec3){0,0,0};
    t_vec3 best_n   = (t_vec3){0,0,0};

    // Compute axis and base
    t_vec3 axis = normalize(obj->o);        // apex -> base
    t_vec3 apex = obj->p;
    t_vec3 base = vec_op_vec(apex, sc_op_vec(obj->h, axis, mul), add);

    // Precompute cone slope
    float h2 = obj->h * obj->h;
    float r2 = obj->r * obj->r;
    float cos2 = (h2 > 0.0f) ? (h2 / (h2 + r2)) : 0.0f;

    // ===== 1) Side intersection =====
    t_vec3 co = vec_op_vec(origin, apex, sub);
    float Da = dot(dir, axis);
    float Oa = dot(co, axis);
    float DD = dot(dir, dir);
    float OO = dot(co, co);
    float DO = dot(dir, co);

    float a = Da*Da - cos2 * DD;
    float b = 2.0f * (Oa*Da - cos2 * DO);
    float c = Oa*Oa - cos2 * OO;
    float delta = b*b - 4.0f*a*c;

    if (delta >= 0.0f && fabsf(a) > EPSILON)
    {
        float sd = sqrtf(fmaxf(delta, 0.0f));
        float t1 = (-b - sd) / (2.0f * a);
        float t2 = (-b + sd) / (2.0f * a);

        float t_side = 0.0f;
        if (t1 > EPS && (t1 < t2 || t2 <= EPS)) t_side = t1;
        else if (t2 > EPS)                      t_side = t2;

        if (t_side > EPS)
        {
            t_vec3 p = vec_op_vec(origin, sc_op_vec(t_side, dir, mul), add);
            float u  = dot(vec_op_vec(p, apex, sub), axis); // height along axis from apex

            // Allow apex and base hits (0..h) including EPS
            if (u >= 0.0f && u <= obj->h)
            {
                if (t_side < best_t)
                {
                    best_t  = t_side;
                    best_poi = p;

                    // Normal for side
                    t_vec3 v = vec_op_vec(p, apex, sub);
                    t_vec3 n = vec_op_vec(sc_op_vec(dot(v, axis), axis, mul),
                                          sc_op_vec(cos2, v, mul), sub);

                    // Handle apex degenerate case
                    if (magnitude(n) < EPS)
                    {
                        // small offset along axis if too small
                        n = axis;
                    }
                    best_n = normalize(n);
                }
            }
        }
    }

    // ===== 2) Base cap intersection =====
    float denom = dot(dir, axis);
    if (fabsf(denom) > EPS)
    {
        float t_cap = dot(vec_op_vec(base, origin, sub), axis) / denom;
        if (t_cap > EPS)
        {
            t_vec3 p = vec_op_vec(origin, sc_op_vec(t_cap, dir, mul), add);
            t_vec3 diff = vec_op_vec(p, base, sub);
            float dist2 = dot(diff, diff);

            if (dist2 <= r2 + EPS)
            {
                if (t_cap < best_t + EPS) // allow tiny overlap with side
                {
                    best_t  = t_cap;
                    best_poi = p;
                    best_n   = axis; // base normal
                }
            }
        }
    }

    // ===== 3) Finalize hit =====
    if (best_t == INF_DIST)
        return (hit.hit = 0, hit);

    // Flip normal to face the ray
    if (dot(best_n, dir) > 0.0f)
        best_n = sc_op_vec(-1.0f, best_n, mul);

    hit.poi    = best_poi;
    hit.normal = best_n;
    hit.dist   = distance(best_poi, origin);
    hit.color  = get_color(best_poi, obj);
    hit.obj    = obj;
    hit.light  = 0;
    hit.hit    = 1;

    return hit;
}
