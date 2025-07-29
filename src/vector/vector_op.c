#include <miniRT.h>

float dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vec_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return result;
}

float distance(t_vec3 vec1, t_vec3 vec2)
{
    return (sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2) + pow(vec1.z - vec2.z, 2)));
}

t_vec3 cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 out;

	out.x = vec1.y * vec1.z - vec1.z * vec2.y;
	out.y = vec1.z * vec1.x - vec1.x * vec2.z;
	out.z = vec1.x * vec1.y - vec1.y * vec2.x;
	return (out);
}

t_vec3 vec_op_vec(t_vec3 vec1, t_vec3 vec2, float (*op)(float, float))
{
	t_vec3 result;

	result.x = op(vec1.x, vec2.x);
	result.y = op(vec1.y, vec2.y);
	result.z = op(vec1.z, vec2.z);
	return (result);
}

t_vec3 sc_op_vec(float sc, t_vec3 vec2, float (*op)(float, float))
{
	t_vec3 result;

	result.x = op(sc, vec2.x);
	result.y = op(sc, vec2.y);
	result.z = op(sc, vec2.z);
	return (result);
}	
