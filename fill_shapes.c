/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:00:40 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 12:13:18 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	fill_plan(t_minirt *vars, char *line, t_object *obj)
{
	(void)vars;
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type);
		if (type == VECTOR || type == ORIENT || type == RGB || type == RGB1)
			obj->crd = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(PLAN), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type);
		if (type == ORIENT || type == RGB1)
			obj->n_vct = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(PLAN), 1);
	}
	if (fields && fields[3])
	{
		data = classifier(fields[3], &type);
		c = (t_color *)data;
		if (type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0))
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), throw_error(PLAN), 1);
		obj->class = PLAN;
	}
	return (ft_free("2", fields), 0);
}

int	fill_cylinder(t_minirt *vars, char *line, t_object *obj)
{
	(void)vars;
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type);
		if (type == VECTOR || type == ORIENT || type == RGB || type == RGB1)
			obj->crd = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(CYLINDER), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type);
		if (type == ORIENT || type == RGB1)
			obj->o_vct = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(CYLINDER), 1);
	}
	if (fields && fields[3])
	{
		data = classifier(fields[3], &type);
		if (type >= RATIO)
			obj->d = *(float *)data;
		else
			return (ft_free("2", fields), throw_error(CYLINDER), 1);
		obj->class = CYLINDER;
	}
	if (fields && fields[4])
	{
		data = classifier(fields[4], &type);
		if (type >= RATIO)
			obj->h = *(float *)data;
		else
			return (ft_free("2", fields), throw_error(CYLINDER), 1);
		obj->class = CYLINDER;
	}
	if (fields && fields[5])
	{
		data = classifier(fields[5], &type);
		c = (t_color *)data;
		if (type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0))
			obj->h = *(float *)data;
		else
			return (ft_free("2", fields), throw_error(CYLINDER), 1);
		obj->class = CYLINDER;
	}
	return (ft_free("2", fields), 0);
}

int	fill_sphere(t_minirt *vars, char *line, t_object *obj)
{
	(void)vars;
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type);
		if (type == VECTOR || type == ORIENT || type == RGB || type == RGB1)
			obj->crd = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(SPHERE), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type);
		if (type >= RATIO)
			obj->d = *(float *)data;
		else
			return (ft_free("2", fields), throw_error(LIGHT), 1);
	}
	if (fields && fields[3])
	{
		data = classifier(fields[3], &type);
		c = (t_color *)data;
		if (type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0))
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), throw_error(CAMERA), 1);
		obj->class = SPHERE;
	}
	return (ft_free("2", fields), 0);
}
