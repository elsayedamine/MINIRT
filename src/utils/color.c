/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:24:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:25:55 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_color	int_to_color(int in)
{
	t_color	out;

	out.r = (in >> 16) & 0xFF;
	out.g = (in >> 8) & 0xFF;
	out.b = in & 0xFF;
	return (out);
}

int	color_to_int(t_color color)
{
	int	result;

	result = (color.r << 16) | (color.g << 8) | color.b;
	return (result);
}

t_color	col_mul_col(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r * c2.r) / 255;
	result.g = (c1.g * c2.g) / 255;
	result.b = (c1.b * c2.b) / 255;
	return (result);
}

t_color	col_mul_sc(t_color col, float sc)
{
	t_color	result;

	result.r = (int)(sc * (float)col.r);
	result.g = (int)(sc * (float)col.g);
	result.b = (int)(sc * (float)col.b);
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

t_color	col_add_col(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}
