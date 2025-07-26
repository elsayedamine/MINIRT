/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:36:35 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 17:16:03 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_ambiance(char *line, t_object *obj)
{
	char	**fields;
	int		type;
	void	*data;

	fields = ft_split(line, WHITE);
	if (!fields || !obj)
		return (1);
	obj->class = AMBIANCE;
	data = classifier(fields[1], &type, &obj->crd, &obj->rgb);
	if (type < RATIO)
		return (ft_free("2", fields), throw_error(AMBIANCE), 1);
	obj->ratio = *(float *)data;
	data = classifier(fields[2], &type, &obj->crd, &obj->rgb);
	if (type != RGB)
		return (ft_free("2", fields), throw_error(AMBIANCE), 1);
	obj->rgb = *(t_color *)data;
	return (ft_free("2", fields), 0);
}

int	fill_camera(char *line, t_object *obj)
{
	char	**fields;
	void	*data;
	int		type;

	fields = ft_split(line, WHITE);
	if (!fields || !obj)
		return (1);
	obj->class = CAMERA;
	data = classifier(fields[1], &type, &obj->crd, &obj->rgb);
	if (!data || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(CAMERA), 1);
	obj->crd = *(t_vec3 *)data;
	data = classifier(fields[2], &type, &obj->crd, &obj->rgb);
	if (type != ORIENT && type != RGB1)
		return (ft_free("2", fields), throw_error(CAMERA), 1);
	obj->o_vct = *(t_vec3 *)data;
	data = classifier(fields[3], &type, &obj->crd, &obj->rgb);
	if (type != FOV && type != RATIO)
		return (ft_free("2", fields), throw_error(CAMERA), 1);
	obj->fov = *(float *)data;
	return (ft_free("2", fields), 0);
}

int	fill_light(char *line, t_object *obj)
{
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (!fields)
		return (1);
	obj->class = LIGHT;
	data = classifier(fields[1], &type, &obj->crd, &obj->rgb);
	if (!data || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(LIGHT), 1);
	obj->crd = *(t_vec3 *)data;
	data = classifier(fields[2], &type, &obj->crd, &obj->rgb);
	if (type != RATIO)
		return (ft_free("2", fields), throw_error(LIGHT), 1);
	obj->ratio = *(float *)data;
	data = classifier(fields[3], &type, &obj->crd, &obj->rgb);
	c = (t_color *)data;
	if (type != RGB && (type != RGB1 || c->r < 0 || c->g < 0 || c->b < 0))
		return (ft_free("2", fields), throw_error(LIGHT), 1);
	obj->rgb = *(t_color *)data;
	return (ft_free("2", fields), 0);
}
