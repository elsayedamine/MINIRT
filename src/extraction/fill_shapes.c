/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:00:40 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/08 02:05:20 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	fill_plan(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4 + 1)
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->class = PLAN;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->n = data.p;
	data = classifier(fields[3], &type, RGB);
	obj->t.c1 = data.t.c1;
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	if (fields[4])
		obj->t = extract_texture(fields[4], vars);
	if (fields[4] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(PLAN), 1);
	return (ft_free("2", fields), 0);
}

int	fill_cylinder(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 6 + 1)
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->class = CYLINDER;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->o = data.p;
	data = classifier(fields[3], &type, CYLINDER);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->r = data.r / 2.0f;
	data = classifier(fields[4], &type, CYLINDER);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->h = data.r;
	data = classifier(fields[5], &type, RGB);
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->t.c1 = data.t.c1;
	if (fields[6])
		obj->t = extract_texture(fields[6], vars);
	if (fields[6] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	return (ft_free("2", fields), 0);
}

int	fill_sphere(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4 + 1)
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->class = SPHERE;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, SPHERE);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->r = data.r / 2.0f;
	data = classifier(fields[3], &type, RGB);
	obj->t.c1 = data.t.c1;
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	if (fields[4])
		obj->t = extract_texture(fields[4], vars);
	if (fields[4] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	return (ft_free("2", fields), 0);
}

int	fill_cone(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 6 + 1)
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->class = CONE;
	obj->t.mode = NONE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->o = data.p;
	data = classifier(fields[3], &type, CONE);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->angle = data.r;
	data = classifier(fields[4], &type, CONE);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->h = data.r;
	data = classifier(fields[5], &type, RGB);
	if (!(type == RGB || (type == RGB1 && obj->t.c1.r >= 0 && obj->t.c1.g >= 0 && obj->t.c1.b >= 0)))
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->t.c1 = data.t.c1;
	if (fields[6])
		obj->t = extract_texture(fields[6], vars);
	if (fields[6] && obj->t.mode == NONE)
		return (ft_free("2", fields), throw_error(CONE), 1);
	return (ft_free("2", fields), 0);
}
