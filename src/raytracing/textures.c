#include <miniRT.h>

t_vec3 get_uv_cone(t_vec3 poi, t_object *obj)
{
	t_vec3 local;
	t_vec3 uv;
	t_vec3 rel;

	rel = vec_op_vec(poi, obj->p, sub);
	local.x = dot(rel, obj->tan);
	local.y = dot(rel, obj->o);
	local.z = dot(rel, obj->bitan);
	local = sc_op_vec(1.0f / obj->r, local, mul);	
	uv.x = obj->facing + atan2(local.z, local.x) / (2.0f * M_PI);	
	uv.y = (local.y + obj->h / 2.0f) / obj->h;
	return (uv);
}

t_vec3 get_uv_cylinder(t_vec3 poi, t_object *obj)
{
	t_vec3 local;
	t_vec3 uv;
	t_vec3 rel;

	rel = vec_op_vec(poi, obj->p, sub);
	local.x = dot(rel, obj->tan);
	local.y = dot(rel, obj->o);
	local.z = dot(rel, obj->bitan);
	local = sc_op_vec(1.0f / obj->r, local, mul);	
	uv.x = obj->facing + atan2(local.z, local.x) / (2.0f * M_PI);
	uv.y = 1.0f - local.y / obj->h;
	return (uv);
}

t_vec3 get_uv_plane(t_vec3 poi, t_object *obj)
{
	t_vec3 up;
	t_vec3 local;
	t_vec3 uv;
	t_vec3 ref;
	t_vec3 right;

	local = vec_op_vec(poi, obj->p, sub);
	if (obj->n.y < .999f)
		ref = (t_vec3){0, 1, 0};
	else
		ref = (t_vec3){0, 0, -1};
	right = normalize(cross(ref, obj->n));
	up = normalize(cross(right, obj->n));
	uv.x = dot(local, right) * .1f;
	uv.y = dot(local, up) * .1f;
	uv.x = uv.x - floorf(uv.x);
	uv.y = uv.y - floorf(uv.y);
	return (uv);
}

t_vec3 get_uv_sphere(t_vec3 poi, t_object *obj)
{
	t_vec3 local;
	t_vec3 uv;
	t_vec3 rel;

	rel = vec_op_vec(poi, obj->p, sub);
	local.x = dot(rel, obj->tan);
	local.y = dot(rel, obj->o);
	local.z = dot(rel, obj->bitan);
	local = sc_op_vec(1.0f / obj->r, local, mul);	
	uv.x = obj->facing + atan2(local.z, local.x) / (2.0f * M_PI);
	uv.y = acos(local.y) / M_PI;
	return (uv);
}

t_color get_pixel_bump(int x, int y, void *img)
{
	int endian;
	int sl;
	int bpp;
	char *addr;
	int offset;

	addr = mlx_get_data_addr(img, &bpp, &sl, &endian);
	offset = y * sl + x * (bpp / 8);
	return (int_to_color(*(unsigned int *)(addr + offset)));
}

t_color get_pixel_checkered(float x, float y, t_texture texture)
{
	int u = (int)floor(x * (float)texture.w);
	int v = (int)floor(y * (float)texture.w);
	if ((u + v) % 2 == 0)
	    return (texture.c1);
	else
	    return (texture.c2);
}

t_color get_color(t_vec3 poi, t_object *obj)
{
	t_vec3 uv;
	int x;
	int y;
	t_get_uv f[4] = {
		get_uv_sphere,
		get_uv_cylinder,
		get_uv_plane,
		get_uv_cone
	};

	if (obj->t.mode == NONE)
		return (obj->t.c1);
	uv = f[obj->class - 3](poi, obj);
	if (obj->t.mode == CHECKERED)
		return (get_pixel_checkered(uv.x, uv.y, obj->t));
	x = (1.0f - uv.x) * (float)(obj->t.w - 1);
	y = uv.y * (float)(obj->t.h - 1);
	if (obj->t.mode == BUMPMAP)
		return (get_pixel_bump(x, y, obj->t.img));
	return (obj->t.c1);
}
