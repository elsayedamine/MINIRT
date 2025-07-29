#include <miniRT.h>

t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	(void)origin;
	(void)dir;
	(void)obj;
	t_hit_info dummy;

	dummy.light = 0;
	return dummy;
}

t_hit_info	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	t_hit_info dummy;

	// equation du rayon (droite) f(x) = ax + b
	// tel que a (la pente) vecteur directeur
	// et b l'ordonnee a l'origin (t_vec origin)
	// donc f(x) = dir.x + cam_origin
	// equation d'une sphere : |x - o|^2 = r^2
	// tq x sont les points du sphere, r le rayon et o l'origin
	// on substit, l'equation du rayon du camera dans l'eq du sphere
	// on obtient : | dir.x + cam_origin, sphere_origin|^2 = r^2;
	// on pose OC = cam_origin - sphere_origin;
	// on develop l'equation : (dir^2).x^2 + 2.OC.dir.x + OC^2 - r^2 = 0;
	// on solve l equtions avec descriminent Delta
	// Δ = 4.(OC.dir)^2 - 4.dir^2.(OC^2 - r^2);
	// Δ = B^2 - 4.A.C
	// si Δ < 0 pat de point dintersection
	// si Δ > 0 2 pts dinterection on prend le plus petit qui est le premier
	// si Δ == 0 un point d'intersection (la tangante au sphere)
	// alors x = (-B + racine(Δ)) / 2A; ou  x = (-B - racine(Δ)) / 2A;
	// START TO CODE::::::::::::::::::::
	
	// the equation A.x^2 + B.x + C;
	float	a = dot(dir, dir);
	float	b = 2 * dot(vec_sub(origin, obj->crd), dir);
	float	c = dot(vec_sub(origin, obj->crd), vec_sub(origin, obj->crd)) - obj->r * obj->r;
	float	delta = pow(b, 2) - 4 * a * c;
	float	x1 = (-b + sqrt(delta)) / 2 * a;
	float	x2 = (-b - sqrt(delta)) / 2 * a;
	if (delta < 0) // no intersection
		(dummy.hit = 0, dummy);
	dummy.hit = 0;
	dummy.poi = fmin(x1, x2);
	dummy.normal = normalise(vec_sub(poi, obj->crd));
	dummy.dist = dot(vec_sub(dummy.poi, origin), dir);
	dummy.color = obj->rgb;
	dummy.light = 0;
	dummy.obj = obj;
	return (dummy);
}

t_hit_info	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	(void)origin;
	(void)dir;
	(void)obj;
	t_hit_info dummy;

	dummy.light = 0;
	return dummy;
}

t_hit_info	intersect_plan(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	(void)origin;
	(void)dir;
	(void)obj;
	t_hit_info dummy;

	dummy.light = 0;
	return dummy;
}

t_hit_info	intersect_last_shape(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	(void)origin;
	(void)dir;
	(void)obj;
	t_hit_info dummy;

	dummy.light = 0;
	return dummy;
}
