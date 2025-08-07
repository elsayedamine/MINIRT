/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:48:49 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/07 23:52:10 by sayed            ###   ########.fr       */
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
	obj.r = -2.0f;
	obj.h = -2.0f;
	obj.p.x = 0;
	obj.p.y = 0;
	obj.p.z = 0;
	obj.n.x = 0;
	obj.n.y = 0;
	obj.n.z = 0;
	obj.o.x = 0;
	obj.o.y = 0;
	obj.o.z = 0;
	obj.rgb.r = 0;
	obj.rgb.g = 0;
	obj.rgb.b = 0;

	if (s && split_3_parts(s, p[0], p[1], p[2]))
	{
		if (class == RGB && is_int(p[0]) && is_int(p[1]) && is_int(p[2]) && \
			fill_rgb(&obj.rgb, p[0], p[1], p[2]) < 5)
			return (*type = fill_rgb(&obj.rgb, p[0], p[1], p[2]), obj);
		if (fill_vector(&obj.p, p, class, type) == TRUE)
			return (obj);
	}
	else if (s && fill_float(&obj.r, s) >= 5)
		return (*type = fill_float(&obj.r, s), \
			obj.class = fill_float(&obj.r, s), obj);
	return (*type = UNKNOWN, obj.class = UNKNOWN, obj);
}

// t_mode set_mode(t_minirt *vars, char *str, t_object *obj)
// {
// 	int len;
// 	char *cpy;
	
// 	if (!ft_strncmp("c", str, 1))
// 	{
// 		obj->t.mode = CHECKERED;
// 		return (CHECKERED);
// 	}
// 	cpy = str;
// 	len = ft_strlen(cpy) - 1;
// 	if (len + 1 < 7)
// 		return (NONE);
// 	if (!ft_strncmp(&cpy[len - 3], ".xpm", 4))
// 	{
// 		if (!ft_strncmp(&cpy[len - 5], "_t", 2))
// 			obj->t.mode = TEXTURE;
// 		else if (!ft_strncmp(&cpy[len - 5], "_b", 2))
// 			obj->t.mode = BRUMPMAP;
// 		else
// 			return (NONE);
// 		obj->t.img = mlx_xpm_file_to_image(vars->win.mlx, str, obj->t.w, obj->t.h);
// 		return (obj->t.mode);
// 	}
// 	return (NONE);
// }