/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:32:37 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/25 18:17:35 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	auxilliary_fill_cylinder(t_minirt *vars, t_object *obj, \
							char **fields, char s[7][12])
{
	int			type;
	t_object	data;

	data = classifier(fields[3], &type, CYLINDER);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CYLINDER, s), 1);
	obj->r = data.r / 2.0f;
	obj->shininess = SHININESS;
	data = classifier(fields[4], &type, CYLINDER);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CYLINDER, s), 1);
	obj->h = data.r;
	data = classifier(fields[5], &type, RGB);
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && \
		obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(CYLINDER, s), 1);
	obj->t.c1 = data.t.c1;
	if (fields[6])
		obj->t = extract_texture(fields[6], vars);
	if (fields[6] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(CYLINDER, s), 1);
	obj->ratio = obj->r / obj->h;
	return (ft_free("2", fields), 0);
}

int	fill_cylinder(t_minirt *vars, char *line, t_object *obj, char strs[8][12])
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 6 + 1)
		return (ft_free("2", fields), throw_error(CYLINDER, strs), 1);
	obj->class = CYLINDER;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(CYLINDER, strs), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(CYLINDER, strs), 1);
	obj->o = data.p;
	return (auxilliary_fill_cylinder(vars, obj, fields, strs));
}
