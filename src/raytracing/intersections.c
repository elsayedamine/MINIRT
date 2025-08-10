#include <miniRT.h>

t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	t_vec3		oc;
	float		x1, x2, x;
	float		radius = 5; // just random 7alia

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

t_hit_info	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info hit[3];

	t_vec3 w = vec_op_vec(origin, obj->p, sub);
	t_vec3 d = vec_op_vec(dir, sc_op_vec(dot(dir, obj->o), obj->o, mul), sub);
	t_vec3 m = vec_op_vec(w, sc_op_vec(dot(w, obj->o), obj->o, mul), sub);
	float a = dot(d, d);
	if (fabs(a) < EPSILON)
		return (hit[0].hit = 0, hit[0]);
	float b = 2 * dot(m, d);
	float c = dot(m, m) - pow(obj->r, 2);
	float delta = pow(b, 2) - 4 * a * c;
	if (delta < 0.0f)
		return (hit[0].hit = 0, hit[0]);
	float sqrt_delta = sqrtf(fmaxf(delta, 0.0f)); // added to reduce black spots
	float x1 = (-b - sqrt_delta) / (2 * a);
	float x2 = (-b + sqrt_delta) / (2 * a);
	float x = 0;
	if (x1 > EPS_HIT && (x1 < x2 || x2 <= EPS_HIT))
	    x = x1;
	else if (x2 > EPS_HIT)
	    x = x2;
	else
	    return (hit[0].hit = 0, hit[0]);
	hit[0].poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	float spot = dot(vec_op_vec(hit[0].poi, obj->p, sub), obj->o);
	if (spot < 0 || spot > obj->h)
		return (hit[0].hit = 0, hit[0]);
	hit[0].hit = 1;
	// added these two lines too
	t_vec3 proj = sc_op_vec(dot(vec_op_vec(hit[0].poi, obj->p, sub), obj->o), obj->o, mul);
	hit[0].normal = normalize(vec_op_vec(vec_op_vec(hit[0].poi, obj->p, sub), proj, sub));
	hit[0].dist = distance(hit[0].poi, origin);
	hit[0].color = get_color(hit[0].poi, obj);
	hit[0].obj = obj;
	hit[0].light = 0;
	return (calculate_intersection_with_bases(obj, hit, (t_ray){.dir = dir, .origin = origin}));
}

t_hit_info	calculate_intersection_with_bases(t_object *cylinder, t_hit_info hit[3], t_ray ray)
{
	t_vec3	top_center = vec_op_vec(cylinder->p, sc_op_vec(cylinder->h, cylinder->o, mul), add);
	t_vec3	bottome_center = cylinder->p;
	t_object	plane;
	plane.t = cylinder->t;
	plane.class = PLAN;
	plane.n = cylinder->o;
	plane.p = top_center;
	hit[1] = intersect_plane(ray.origin, ray.dir, &plane);
	plane.p = bottome_center;
	hit[2] = intersect_plane(ray.origin, ray.dir, &plane);
	float	min_dist = hit[0].dist;
	if (hit[1].hit && distance(hit[1].poi, top_center) > cylinder->r)
	        hit[1].hit = 0;
	if (hit[2].hit && distance(hit[2].poi, bottome_center) > cylinder->r)
	        hit[2].hit = 0;
	if (hit[1].hit)
	{
		min_dist = hit[1].dist;
		if (hit[2].hit)
			min_dist = fmin(hit[1].dist, hit[2].dist);
	}
	min_dist = fmin(min_dist, hit[0].dist);
	if (min_dist == hit[0].dist)
		return (hit[0]);
	if (min_dist == hit[1].dist)
		return (hit[1]);
	else
		return (hit[2]);
}

t_hit_info	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info hit;

	if (dot(obj->n, dir) == 0)
		return (hit.hit = 0, hit);
	float	x = (dot(obj->n, vec_op_vec(obj->p, origin, sub))) / dot(obj->n, dir);
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

t_hit_info	intersect_cone(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info hit;

	t_vec3 w = vec_op_vec(origin, obj->p, sub);
	float k = pow(cos(obj->angle * RAD), 2);
	float a = pow(dot(dir, obj->o), 2) - k * dot(dir, dir);
	if (fabs(a) < EPSILON)
		return (hit.hit = 0, hit);
	float b = 2 * dot(w, obj->o) * dot(dir, obj->o) - 2 * k * dot(w, dir);
	float c = pow(dot(w, obj->o), 2) - k * dot(w, w);
	float delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (hit.hit = 0, hit);
	float sqrt_delta = sqrtf(fmaxf(delta, 0.0f));
	float x1 = (-b - sqrt_delta) / (2 * a);
	float x2 = (-b + sqrt_delta) / (2 * a);
	float x = 0.0f;
	if (x1 > EPS_HIT && (x1 < x2 || x2 <= EPS_HIT))
	    x = x1;
	else if (x2 > EPS_HIT)
	    x = x2;
	else
	    return (hit.hit = 0, hit);
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	float spot = dot(vec_op_vec(hit.poi, obj->p, sub), obj->o);
	if (spot < 0 || spot > obj->h)
		return (hit.hit = 0, hit);
	// i added the two lines below
	t_vec3 axis = sc_op_vec(dot(obj->o, vec_op_vec(hit.poi, obj->p, sub)), obj->o, mul);
	hit.normal = normalize(vec_op_vec(vec_op_vec(hit.poi, obj->p, sub), axis, sub));
	hit.hit = 1;
	hit.dist = distance(hit.poi, origin);
	hit.color = get_color(hit.poi, obj);
	hit.obj = obj;
	hit.light = 0;
	return (hit);

}
