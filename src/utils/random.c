#include <miniRT.h>
#include <stdint.h>

unsigned int ptr_to_seed(void *ptr)
{
	uintptr_t addr;

	addr = (uintptr_t)ptr;
	return ((unsigned int)(addr & 0xFFFFFFFF)) ^ ((unsigned int)(addr >> 32));
}

unsigned int _random(void *state)
{
	unsigned int seed;
	unsigned int result;

	seed = ptr_to_seed(state) * 747796405 + 2891336453;
	result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
	result = (result >> 22) ^ result;
	return (result);
}

float random_float(void *state)
{
	unsigned int rand_int;

	rand_int = _random(state);
	return (rand_int / (float)UINT_MAX);
}

float rrand(void *state, float min, float max)
{
	float _rand;

	_rand = random_float(state);
	return (min + _rand * (max - min));
}
