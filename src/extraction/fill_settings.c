/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:36:35 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/25 18:18:12 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	fill_ambiance(char *line, t_minirt *vars, char strs[8][12])
{
	char		**fields;
	int			type;
	t_object	data;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 3)
		return (ft_free("2", fields), throw_error(AMBIANCE, strs), 1);
	data = classifier(fields[1], &type, AMBIANCE);
	if (type != RATIO)
		return (ft_free("2", fields), throw_error(AMBIANCE, strs), 1);
	vars->amb_ratio = data.r;
	data = classifier(fields[2], &type, RGB);
	if (type != RGB && type != RGB1)
		return (ft_free("2", fields), throw_error(AMBIANCE, strs), 1);
	vars->amb_rgb = data.t.c1;
	vars->amb = 1;
	return (ft_free("2", fields), 2);
}

int	fill_camera(char *line, t_minirt *vars, char strs[8][12])
{
	char		**fields;
	t_object	data;
	int			type;
	static int	cam_number;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4)
		return (ft_free("2", fields), throw_error(CAMERA, strs), 1);
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(CAMERA, strs), 1);
	vars->cam[cam_number].p = data.p;
	data = classifier(fields[2], &type, ORIENT);
	if (type != ORIENT && type != RGB1)
		return (ft_free("2", fields), throw_error(CAMERA, strs), 1);
	vars->cam[cam_number].fw = data.p;
	data = classifier(fields[3], &type, CAMERA);
	if (type != FOV && type != RATIO)
		return (ft_free("2", fields), throw_error(CAMERA, strs), 1);
	vars->cam[cam_number].fov = data.r;
	if (++cam_number >= 11)
		return (ft_free("2", fields), throw_error(TOO_MANY_CAM, NULL), 1);
	vars->cam[cam_number - 1].exist = 1;
	set_obj_vec(vars->cam + cam_number - 1, CAMERA);
	return (ft_free("2", fields), 2);
}

int	fill_light(char *line, t_object *obj, char strs[8][12])
{
	char		**fields;
	t_object	data;
	int			type;

	fields = ft_split(line, WHITE);
	if (!fields || ft_arrlen(fields) > 4)
		return (ft_free("2", fields), throw_error(LIGHT, strs), 1);
	obj->class = LIGHT;
	data = classifier(fields[1], &type, VECTOR);
	if (data.class == UNKNOWN || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(LIGHT, strs), 1);
	obj->p = data.p;
	data = classifier(fields[2], &type, LIGHT);
	if (type != RATIO)
		return (ft_free("2", fields), throw_error(LIGHT, strs), 1);
	obj->ratio = data.r;
	data = classifier(fields[3], &type, RGB);
	obj->t.c1 = data.t.c1;
	if (type != RGB && (type != RGB1 || obj->t.c1.r < 0 || \
		obj->t.c1.g < 0 || obj->t.c1.b < 0))
		return (ft_free("2", fields), throw_error(LIGHT, strs), 1);
	return (ft_free("2", fields), 0);
}
