/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:48:49 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 23:08:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	split_3_parts(char *s, char part1[8], char part2[8], char part3[8])
{
	int	i;
	int j;

	ft_init(&i, &j);
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
	part3[j] = '\0';
	return (s[i] == '\0');
}

int	classifier(const char *s)
{
	char	p1[8], p2[8], p3[8];
	t_vec3	v;
	t_color	c;

	if (split_3_parts(s, p1, p2, p3))
	{
		v.x = ft_atof(p1);
		v.y = ft_atof(p2);
		v.z = ft_atof(p3);
		if (!isnan(v.x) && !isnan(v.y) && !isnan(v.z))
			return (VECTOR);
		c.r = ft_atoi(p1);
		c.g = ft_atoi(p2);
		c.b = ft_atoi(p3);
		if (c.r >= 0 && c.r <= 255 && c.g >= 0 && c.g <= 255 && c.b >= 0 && c.b <= 255)
			return (RGB);
	}
	else
	{
		v.x = ft_atof(s);
		if (isnan(v.x))
			return (UNKNOWN);
		if (v.x >= 0.0 && v.x <= 1.0)
			return (RATIO);
		if (v.x > 0.0 && v.x <= 180.0)
			return (FOV);
		if (v.x > 0.0)
			return (FLOAT);
	}
	return (UNKNOWN);
}
