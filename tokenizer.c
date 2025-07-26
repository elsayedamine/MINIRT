/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:48:49 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 12:04:20 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	split_3_parts(char *s, char part1[8], char part2[8], char part3[8])
{
	int	i;
	int j;

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
int	is_strict_int(char *s)
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
void	*classifier(char *s, int *type)
{
	char	p1[8], p2[8], p3[8];
	t_vec3	*v = (t_vec3 *)malloc(sizeof(t_vec3));
	t_color	*c = (t_color *)malloc(sizeof(t_color));

	if (split_3_parts(s, p1, p2, p3))
	{
		if (is_strict_int(p1) && is_strict_int(p2) && is_strict_int(p3))
		{
			c->r = ft_atoi(p1);
			c->g = ft_atoi(p2);
			c->b = ft_atoi(p3);
			if (c->r >= -1 && c->r <= 1 && c->g >= -1 && c->g <= 1 && c->b >= -1 && c->b <= 1)
				return (*type = RGB1, c);
			if (c->r >= 0 && c->r <= 255 && c->g >= 0 && c->g <= 255 && c->b >= 0 && c->b <= 255)
				return (*type = RGB, c);
		}
		v->x = ft_atof(p1);
		v->y = ft_atof(p2);
		v->z = ft_atof(p3);
		if (!isnan(v->x) && !isnan(v->y) && !isnan(v->z))
		{
			if (v->x >= -1.0 && v->x <= 1.0 &&
				v->y >= -1.0 && v->y <= 1.0 &&
				v->z >= -1.0 && v->z <= 1.0)
				return (*type = ORIENT, v);
			return (*type = VECTOR, v);
		}
	}
	else
	{
		v->x = ft_atof(s);
		if (isnan(v->x))
			return (*type = UNKNOWN, NULL);
		if (v->x >= 0.0 && v->x <= 1.0)
			return (*type = RATIO, &v->x);
		if (v->x > 0.0 && v->x <= 180.0)
			return (*type = FOV, &v->x);
		if (v->x > 0.0)
			return (*type = FLOAT, &v->x);
	}
	return (*type = UNKNOWN, NULL);
}
