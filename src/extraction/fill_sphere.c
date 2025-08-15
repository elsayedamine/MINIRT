/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:33:22 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 00:44:48 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	auxilliary_fill_sphere(t_minirt *vars, t_object *obj, 
	char **fields, char s[7][12])
{
	int			type;
	t_object	data;

	data = classifier(fields[3], &type, RGB);
	obj->t.c1 = data.t.c1;
	obj->shininess = SHININESS;
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && \
		obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(SPHERE, s), 1);
	if (fields[4])
		obj->t = extract_texture(fields[4], vars);
	if (fields[4] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(SPHERE, s), 1);
	return (ft_free("2", fields), 0);
}

int	fill_sphere(t_minirt *vars, char *line, t_object *obj, char strs[7][12])
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4 + 1)
		return (ft_free("2", fields), throw_error(SPHERE, strs), 1);
	obj->class = SPHERE;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(SPHERE, strs), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, SPHERE);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(SPHERE, strs), 1);
	obj->r = data.r / 2.0f;
	return (auxilliary_fill_sphere(vars, obj, fields, strs));
}
