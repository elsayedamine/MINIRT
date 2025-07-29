/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:48:49 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/28 17:45:57 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <miniRT.h>

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

t_object	classifier(char *s, int *type, int class)
{
	char	p[3][8];
	t_object obj;
	obj.class = -1;
	obj.ratio = -2.0f;
	obj.fov = -2.0f;
	obj.d = -2.0f;
	obj.h = -2.0f;
	obj.crd.x = 0;
	obj.crd.y = 0;
	obj.crd.z = 0;
	obj.n_vct.x = 0;
	obj.n_vct.y = 0;
	obj.n_vct.z = 0;
	obj.o_vct.x = 0;
	obj.o_vct.y = 0;
	obj.o_vct.z = 0;
	obj.rgb.r = 0;
	obj.rgb.g = 0;
	obj.rgb.b = 0;

	if (s && split_3_parts(s, p[0], p[1], p[2]))
	{
		if (class == RGB && is_int(p[0]) && is_int(p[1]) && is_int(p[2]) && \
			fill_rgb(&obj.rgb, p[0], p[1], p[2]) < 5)
			return (*type = fill_rgb(&obj.rgb, p[0], p[1], p[2]), obj);
		if (fill_vector(&obj.crd, p, class, type) == TRUE)
			return (obj);
	}
	else if (s && fill_float(&obj.d, s) >= 5)
		return (*type = fill_float(&obj.d, s), \
			obj.class = fill_float(&obj.d, s), obj);
	return (*type = UNKNOWN, obj.class = UNKNOWN, obj);
}
