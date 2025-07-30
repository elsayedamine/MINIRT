#include <miniRT.h>

t_color init_color(int a, int r, int g, int b)
{
	t_color out;

	out.a = a;
	out.r = r;
	out.g = g;
	out.b = b;
	return (out);
}

t_color int_to_color(int in)
{
	t_color out;

	out.a = (in >> 24) & 0xFF;
	out.r = (in >> 16) & 0xFF;
	out.g = (in >> 8) & 0xFF;
	out.b = in & 0xFF;
	return (out);
}

int color_to_int(t_color color)
{
	int result;

	result = (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
	return (result);
}

t_color col_mul_col(t_color c1, t_color c2)
{
	t_color result;

	result.a = (c1.a * c2.a) / 255;
	result.r = (c1.r * c2.r) / 255;
	result.g = (c1.g * c2.g) / 255;
	result.b = (c1.b * c2.b) / 255;
	return (result);
}

t_color col_mul_sc(t_color col, float sc)
{
	t_color result;

	result.a = (int)(sc * (float)col.a);
	result.r = (int)(sc * (float)col.r);
	result.g = (int)(sc * (float)col.g);
	result.b = (int)(sc * (float)col.b);	
	if (result.a > 255)
		result.a = 255;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

t_color col_add_col(t_color c1, t_color c2)
{
	t_color result;

	result.a = c1.a + c2.a;
	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	
	if (result.a > 255) result.a = 255;
	if (result.r > 255) result.r = 255;
	if (result.g > 255) result.g = 255;
	if (result.b > 255) result.b = 255;
	
	return (result);
}
