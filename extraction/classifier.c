/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:48:49 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 21:56:34 by aelsayed         ###   ########.fr       */
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

int	is_int(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	split_3_parts(char *s, char part1[8], char part2[8], char part3[8])
{
	int	i;
	int	j;

	ft_init(2, &i, &j);
	if (s[i] == ',' || s[i] == '\0')
		return (FALSE);
	while (s[i] && s[i] != ',' && j < 7)
		part1[j++] = s[i++];
	part1[j] = '\0';
	if (s[i++] != ',')
		return (FALSE);
	j = 0;
	if (s[i] == ',' || s[i] == '\0')
		return (FALSE);
	while (s[i] && s[i] != ',' && j < 7)
		part2[j++] = s[i++];
	part2[j] = '\0';
	if (s[i++] != ',')
		return (FALSE);
	j = 0;
	if (s[i] == ',' || s[i] == '\0')
		return (FALSE);
	while (s[i] && j < 7)
		part3[j++] = s[i++];
	return (part3[j] = '\0', (s[i] == '\0'));
}

void	*classifier(char *s, int *type, int class)
{
	char	p[3][8];
	float	f;
	float	*fp;
	t_vec3	*v;
	t_color	*c;

	fp = &f;
	v = (t_vec3 *)malloc(sizeof(t_vec3));
	c = (t_color *)malloc(sizeof(t_color));
	if (!v || !c)
		return (free(v), free(c), NULL);
	if (s && split_3_parts(s, p[0], p[1], p[2]))
	{
		if (class == RGB && is_int(p[0]) && is_int(p[1]) && is_int(p[2]) && \
			fill_rgb(c, p[0], p[1], p[2]) < 5)
			return (*type = fill_rgb(c, p[0], p[1], p[2]), c);
		v->x = ft_atof(p[0]);
		v->y = ft_atof(p[1]);
		v->z = ft_atof(p[2]);
		if ((class == VECTOR || class == ORIENT) && \
			!isnan(v->x) && !isnan(v->y) && !isnan(v->z))
		{
			if (v->x >= -1.0 && v->x <= 1.0 && \
				v->y >= -1.0 && v->y <= 1.0 && \
				v->z >= -1.0 && v->z <= 1.0)
				return (*type = ORIENT, v);
			return (*type = VECTOR, v);
		}
	}
	else if (s && fill_float(fp, s) >= 5)
		return (*type = fill_float(fp, s), fp);
	return (*type = UNKNOWN, NULL);
}
