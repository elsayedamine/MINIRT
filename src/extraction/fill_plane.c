/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:32:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 19:02:08 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	auxilliary_fill_plan(t_minirt *vars, t_object *obj, char **fields)
{
	int			type;
	t_object	data;

	data = classifier(fields[3], &type, RGB);
	obj->t.c1 = data.t.c1;
	obj->shininess = SHININESS;
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && \
		obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(PLANE), 1);
	if (fields[4])
		obj->t = extract_texture(fields[4], vars);
	if (fields[4] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(PLANE), 1);
	return (ft_free("2", fields), 0);
}

int	fill_plan(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 5)
		return (ft_free("2", fields), throw_error(PLANE), 1);
	obj->class = PLANE;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(PLANE), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(PLANE), 1);
	obj->n = data.p;
	return (auxilliary_fill_plan(vars, obj, fields));
}
