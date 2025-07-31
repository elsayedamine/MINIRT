#include <miniRT.h>

t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info	hit;
	t_vec3		oc;
	float		x1, x2, x;
	float		radius = 5; // just random 7alia

	hit.hit = 0;	
	hit.light = 0;
	oc = vec_op_vec(origin, obj->crd, sub);
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
	hit.dist = x;
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.normal = normalize(vec_op_vec(hit.poi, obj->crd, sub));
	hit.color = obj->rgb;
	hit.light = obj->ratio;
	hit.obj = obj;
	return (hit);
}


t_hit_info	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info hit;
	
	// the equation A.x^2 + B.x + C;
	float	a = dot(dir, dir);
	float	b = 2 * dot(vec_op_vec(origin, obj->crd, sub), dir);
	float	c = dot(vec_op_vec(origin, obj->crd, sub), vec_op_vec(origin, obj->crd, sub)) - obj->r * obj->r;
	float	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0) // no intersection
		return (hit.hit = 0, hit);
	float	x1 = (-b + sqrt(delta)) / (2 * a);
	float	x2 = (-b - sqrt(delta)) / (2 * a);
	float x = (x1 > 0 && (x1 < x2 || x2 <= 0)) * x1 + (x2 > 0 && !(x1 > 0 && (x1 < x2 || x2 <= 0))) * x2;
	if (!(x1 > 0 && (x1 < x2 || x2 <= 0)) && x2 <= 0)
		return (hit.hit = 0, hit);
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.hit = 1;
	hit.normal = normalize(vec_op_vec(hit.poi, obj->crd, sub));
	hit.dist = fmin(x1, x2);
	hit.color = obj->rgb;
	hit.obj = obj;
	hit.light = 0;
	return (hit);
}

t_hit_info	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	(void)origin;
	(void)dir;
	(void)obj;
	t_hit_info hit;

	hit.light = 0;
	return (hit);
}

t_hit_info	intersect_plan(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info hit;

	if (dot(obj->n_vct, dir) == 0) // plan et droite sont coplanaires ou parallels
		return (hit.hit = 0, hit);
	float	x = (dot(obj->n_vct, vec_op_vec(origin, obj->crd, sub))) / dot(obj->n_vct, dir);
	if (x <= 0)
		return (hit.hit = 0, hit);
	hit.hit = 1;
	hit.poi = vec_op_vec(origin, sc_op_vec(x, dir, mul), add);
	hit.normal = obj->n_vct;
	hit.dist = x;
	hit.color = obj->rgb;
	hit.light = 0;

	return (hit);
}

t_hit_info	intersect_last_shape(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	(void)origin;
	(void)dir;
	(void)obj;
	t_hit_info hit;

	hit.light = 0;
	return (hit);
}
