/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:00:40 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/07 22:47:31 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	fill_plan(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4)
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->class = PLAN;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->n = data.p;
	data = classifier(fields[3], &type, RGB);
	obj->rgb = data.rgb;
	if (!(type == RGB || (type == RGB1 && obj->rgb.r >= 0 && obj->rgb.g >= 0 && obj->rgb.b >= 0)))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	return (ft_free("2", fields), 0);
}

int	fill_cylinder(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 6)
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->class = CYLINDER;
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
	if (!(type == RGB || (type == RGB1 && obj->rgb.r >= 0 && obj->rgb.g >= 0 && obj->rgb.b >= 0)))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->rgb = data.rgb;
	// if (fields[6])
	// {
	// 	if (!set_mode(vars, fields[6], obj))
	// }
	return (ft_free("2", fields), 0);
}

int	fill_sphere(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4)
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->class = SPHERE;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, SPHERE);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->r = data.r / 2.0f;
	data = classifier(fields[3], &type, RGB);
	obj->rgb = data.rgb;
	if (!(type == RGB || (type == RGB1 && obj->rgb.r >= 0 && obj->rgb.g >= 0 && obj->rgb.b >= 0)))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	return (ft_free("2", fields), 0);
}

int	fill_cone(t_minirt *vars, char *line, t_object *obj)
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 6)
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->class = CONE;
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
	if (!(type == RGB || (type == RGB1 && obj->rgb.r >= 0 && obj->rgb.g >= 0 && obj->rgb.b >= 0)))
		return (ft_free("2", fields), throw_error(CONE), 1);
	obj->rgb = data.rgb;
	return (ft_free("2", fields), 0);
}
