/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:03:36 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 22:03:46 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_rgb(t_color *c, char p1[8], char p2[8], char p3[8])
{
	c->r = ft_atoi(p1);
	c->g = ft_atoi(p2);
	c->b = ft_atoi(p3);
	if (c->r >= -1 && c->r <= 1 && c->g >= -1 && \
		c->g <= 1 && c->b >= -1 && c->b <= 1)
		return (RGB1);
	if (c->r >= 0 && c->r <= 255 && c->g >= 0 && \
		c->g <= 255 && c->b >= 0 && c->b <= 255)
		return (RGB);
	return (5);
}

int	fill_float(float *f, char *s)
{
	*f = ft_atof(s);
	if (isnan(*f))
		return (UNKNOWN);
	if (*f >= 0.0 && *f <= 1.0)
		return (RATIO);
	if (*f > 0.0 && *f <= 180.0)
		return (FOV);
	if (*f > 0.0)
		return (FLOAT);
	return (UNKNOWN);
}

int	fill_vector(t_vec3 *v, char p[3][8], int class, int *type)
{
	v->x = ft_atof(p[0]);
	v->y = ft_atof(p[1]);
	v->z = ft_atof(p[2]);
	if ((class == VECTOR || class == ORIENT) && \
		!isnan(v->x) && !isnan(v->y) && !isnan(v->z))
	{
		if (v->x >= -1.0 && v->x <= 1.0 && \
			v->y >= -1.0 && v->y <= 1.0 && \
			v->z >= -1.0 && v->z <= 1.0)
			return (*type = ORIENT, TRUE);
		return (*type = VECTOR, TRUE);
	}
	return (FALSE);
}
