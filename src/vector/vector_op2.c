#include <miniRT.h>

t_vec3	init_vec(float x, float y, float z)
{
	t_vec3	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

float magnitude(t_vec3 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_vec3 normalize(t_vec3 vec)
{
	float mag;

	mag = magnitude(vec);
	vec.x /= mag;
	vec.y /= mag;
	vec.z /= mag;
	return (vec);
}