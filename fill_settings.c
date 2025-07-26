/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:36:35 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 12:11:09 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	fill_ambiance(t_minirt *vars, char *line, t_object *obj)
{
    (void)vars; 
	char	**fields;
	void	*data;
	t_color	*c;
	int		type;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type);
		if (type == RATIO)
			obj->ratio = *(float *)data;
		else
			return (ft_free("2", fields), throw_error(AMBIANCE), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type);
		c = (t_color *)data;
		if (type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0))
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), throw_error(AMBIANCE), 1);
		obj->class = AMBIANCE;
	}
	return (ft_free("2", fields), 0);
}

int	fill_camera(t_minirt *vars, char *line, t_object *obj)
{
    (void)vars; 
	char	**fields;
	void	*data;
	int		type;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type);
		if (type == VECTOR || type == ORIENT || type == RGB || type == RGB1)
			obj->crd = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(CAMERA), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type);
		if (type == ORIENT || type == RGB1)
			obj->o_vct = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(CAMERA), 1);
	}
	if (fields && fields[3])
	{
		data = classifier(fields[3], &type);
		if (type == FOV || type == RATIO)
			obj->fov = *(float *)data;
		else
			return (ft_free("2", fields), throw_error(CAMERA), 1);
		obj->class = CAMERA;
	}
	return (ft_free("2", fields), 0);
}

int	fill_light(t_minirt *vars, char *line, t_object *obj)
{
    (void)vars;
	char	**fields;
	void	*data;
	t_color	*c;
	int		type;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type);
		if (type == VECTOR || type == ORIENT || type == RGB || type == RGB1)
			obj->crd = *(t_vec3 *)data;
		else
			return (ft_free("2", fields), throw_error(LIGHT), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type);
		if (type == RATIO)
			obj->ratio = *(float *)data;
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
			return (ft_free("2", fields), throw_error(LIGHT), 1);
		obj->class = LIGHT;
	}
	return (ft_free("2", fields), 0);
}
