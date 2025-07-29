#include <miniRT.h>

void print_vec(t_vec3 vec, int nl)
{
	printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
	if (nl)
		putchar('\n');
}