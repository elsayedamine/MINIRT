#include <miniRT.h>

t_vec3	rotate(t_vec3 vec, t_vec3 rotx, t_vec3 roty, t_vec3 rotz)
{
	t_vec3 out;
	out.x = vec.x * rotx.x + vec.y * rotx.y + vec.z * rotx.z;
	out.y = vec.x * roty.x + vec.y * roty.y + vec.z * roty.z;
	out.z = vec.x * rotz.x + vec.y * rotz.y + vec.z * rotz.z;
	return (out);
}

t_vec3	rotate_z(t_vec3 vec, float angle)
{
	t_vec3	rotx;
	t_vec3	roty;
	t_vec3	rotz;

	rotx = init_vec(cos(angle), -sin(angle), 0);
	roty = init_vec(sin(angle), cos(angle), 0);
	rotz = init_vec(0, 0, 1);
	return (rotate(vec, rotx, roty, rotz));
}

t_vec3	rotate_y(t_vec3 vec, float angle)
{
	t_vec3	rotx;
	t_vec3	roty;
	t_vec3	rotz;

	rotx = init_vec(cos(angle), 0, sin(angle));
	roty = init_vec(0, 1, 0);
	rotz = init_vec(-sin(angle), 0, cos(angle));
	return (rotate(vec, rotx, roty, rotz));
}

t_vec3	rotate_x(t_vec3 vec, float angle)
{
	t_vec3	rotx;
	t_vec3	roty;
	t_vec3	rotz;

	rotx = init_vec(1, 0, 0);
	roty = init_vec(0, cos(angle), -sin(angle));
	rotz = init_vec(0, sin(angle), cos(angle));
	return (rotate(vec, rotx, roty, rotz));
}
