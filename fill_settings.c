/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:36:35 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/25 19:11:27 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	fill_ambiance(t_minirt *vars, char *line, t_object *obj)
{
    (void)vars; 
	char	**fields;
	void	*data;
	int		type1;
	int		type2;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type1);
		if (type1 == RATIO)
			obj->ratio = *(float *)data;
		else if (type1 == RGB)
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type2);
		if (type2 == RATIO && type1 != type2)
			obj->ratio = *(float *)data;
		else if (type2 == RGB && type1 != type2)
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
		obj->class = AMBIANCE;
	}
	return (ft_free("2", fields), free(obj), 0);
}

int	fill_camera(t_minirt *vars, char *line, t_object *obj)
{
    (void)vars; 
	char	**fields;
	void	*data;
	int		type1;
	int		type2;
	int		type3;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type1);
		if (type1 == VECTOR)
			obj->crd = *(t_vec3 *)data;
		else if (type1 == ORIENT)
			obj->o_vct = *(t_vec3 *)data;
		else if ((type1 == FOV || type1 == RATIO))
			obj->fov = *(float *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type2);
		if (type2 == VECTOR && type1 != type2)
			obj->crd = *(t_vec3 *)data;
		else if (type2 == ORIENT && type1 != type2)
			obj->o_vct = *(t_vec3 *)data;
		else if ((type2 == FOV || type2 == RATIO) && type1 < RATIO)
			obj->fov = *(float *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
	}
	if (fields && fields[3])
	{
		data = classifier(fields[3], &type3);
		if (type3 == VECTOR && type1 != type3 && type2 != type3)
			obj->crd = *(t_vec3 *)data;
		else if (type3 == ORIENT && type1 != type3 && type2 != type3)
			obj->o_vct = *(t_vec3 *)data;
		else if ((type3 == FOV || type3 == RATIO) && type1 < RATIO && type2 < RATIO)
			obj->fov = *(float *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
		obj->class = CAMERA;
	}
	return (ft_free("2", fields), free(obj), 0);
}

int	fill_light(t_minirt *vars, char *line, t_object *obj)
{
    (void)vars; 
	char	**fields;
	void	*data;
	int		type1;
	int		type2;
	int		type3;

	fields = ft_split(line, WHITE);
	if (fields && fields[1])
	{
		data = classifier(fields[1], &type1);
		if (type1 == VECTOR)
			obj->crd = *(t_vec3 *)data;
		else if (type1 == RATIO)
			obj->ratio = *(float *)data;
		else if (type1 == RGB)
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
	}
	if (fields && fields[2])
	{
		data = classifier(fields[2], &type2);
		if (type2 == VECTOR && type1 != type2)
			obj->crd = *(t_vec3 *)data;
		else if (type2 == RATIO && type1 != type2)
			obj->ratio = *(float *)data;
		else if (type2 == RGB && type1 != type2)
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
	}
	if (fields && fields[3])
	{
		data = classifier(fields[3], &type3);
		if (type3 == VECTOR && type1 != type3 && type2 != type3)
			obj->crd = *(t_vec3 *)data;
		else if (type3 == RATIO && type1 != type3 && type2 != type3)
			obj->ratio = *(float *)data;
		else if (type3 == RGB && type1 != type3 && type2 != type3)
			obj->rgb = *(t_color *)data;
		else
			return (ft_free("2", fields), free(obj), throw_error(AMBIANCE), 1);
		obj->class = LIGHT;
	}
	return (ft_free("2", fields), free(obj), 0);
}
