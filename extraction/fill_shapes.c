/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:00:40 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 17:20:34 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_plan(char *line, t_object *obj)
{
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (!fields)
		return (1);
	obj->class = PLAN;
	data = classifier(fields[1], &type, &obj->crd, &obj->rgb);
	if (!data || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->crd = *(t_vec3 *)data;
	data = classifier(fields[2], &type, &obj->crd, &obj->rgb);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->n_vct = *(t_vec3 *)data;
	data = classifier(fields[3], &type, &obj->crd, &obj->rgb);
	c = (t_color *)data;
	if (!(type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0)))
		return (ft_free("2", fields), throw_error(PLAN), 1);
	obj->rgb = *(t_color *)data;
	return (ft_free("2", fields), 0);
}

int	fill_cylinder(char *line, t_object *obj)
{
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (!fields)
		return (1);
	obj->class = CYLINDER;
	data = classifier(fields[1], &type, &obj->crd, &obj->rgb);
	if (!data || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->crd = *(t_vec3 *)data;
	data = classifier(fields[2], &type, &obj->crd, &obj->rgb);
	if (!(type == ORIENT))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->o_vct = *(t_vec3 *)data;
	data = classifier(fields[3], &type, &obj->crd, &obj->rgb);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->d = *(float *)data;
	data = classifier(fields[4], &type, &obj->crd, &obj->rgb);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->h = *(float *)data;
	data = classifier(fields[5], &type, &obj->crd, &obj->rgb);
	c = (t_color *)data;
	if (!(type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0)))
		return (ft_free("2", fields), throw_error(CYLINDER), 1);
	obj->rgb = *c;
	return (ft_free("2", fields), 0);
}

int	fill_sphere(char *line, t_object *obj)
{
	char	**fields;
	void	*data;
	int		type;
	t_color	*c;

	fields = ft_split(line, WHITE);
	if (!fields)
		return (1);
	data = classifier(fields[1], &type, &obj->crd, &obj->rgb);
	if (!data || !(type <= RGB1))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->crd = *(t_vec3 *)data;
	data = classifier(fields[2], &type, &obj->crd, &obj->rgb);
	if (!(type >= RATIO))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->d = *(float *)data;
	data = classifier(fields[3], &type, &obj->crd, &obj->rgb);
	c = (t_color *)data;
	if (!(type == RGB || (type == RGB1 && c->r >= 0 && c->g >= 0 && c->b >= 0)))
		return (ft_free("2", fields), throw_error(SPHERE), 1);
	obj->rgb = *c;
	obj->class = SPHERE;
	return (ft_free("2", fields), 0);
}
