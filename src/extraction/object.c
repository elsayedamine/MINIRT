/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:54:09 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 20:46:59 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_object	*new_object(void)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->o = (t_vec3){0, 0, 1};
	obj->facing = 0;
	obj->class = -1;
	obj->angle = -1;
	obj->r = -2.0;
	obj->h = -2.0;
	obj->ratio = -2.0;
	return (obj);
}

int	assign_object(t_minirt *vars, char *file, t_object *obj, t_list **list)
{
	static int	err;
	static int	seen;

	ft_strcompress(file);
	if (!file[0] || *file == '#')
		return (free(obj), TRUE);
	err = parse_object_line(vars, file, obj, &seen);
	if (err == -1)
		return (free(obj), throw_error(ERR, NULL), 0);
	if (err == 1)
		return (free(obj), 0);
	if (err == 2)
		return (free(obj), TRUE);
	set_obj_vec(obj, obj->class);
	ft_lstadd_back(list, ft_lstnew(obj));
	return (1);
}

void	set_obj_vec(void *object, int type)
{
	t_vec3		vec;
	t_object	*obj;
	t_camera	*cam;
	t_vec3		ref;

	ref = (t_vec3){0, 0, 1};
	if (type == CAMERA)
	{
		cam = (t_camera *)object;
		if (fabs(cam->fw.x) == 0 && fabs(cam->fw.y) == 0)
			ref = (t_vec3){0, 1, 0};
		cam->rt = normalize(cross(cam->fw, ref));
		cam->up = normalize(cross(cam->rt, cam->fw));
		return ;
	}
	obj = (t_object *)object;
	vec = obj->o;
	if (type == PLANE)
		vec = obj->n;
	if (vec.y < .999f)
		ref = (t_vec3){0, 1, 0};
	obj->tan = normalize(cross(ref, vec));
	obj->bitan = normalize(cross(obj->tan, vec));
}
