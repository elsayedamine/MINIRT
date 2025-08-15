/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 16:37:04 by aelsayed         ###   ########.fr       */
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

int	parse_object_line(t_minirt *vars, char *file, t_object *obj, int *seen)
{
	if (!ft_strncmp("A ", file, 2) && !(*seen)++)
		return (fill_ambiance(file, vars));
	if (!ft_strncmp("c ", file, 2))
		return (fill_camera(file, vars));
	if (!ft_strncmp("l ", file, 2))
		return (fill_light(file, obj));
	if (!ft_strncmp("sp ", file, 3))
		return (fill_sphere(vars, file, obj));
	if (!ft_strncmp("cy ", file, 3))
		return (fill_cylinder(vars, file, obj));
	if (!ft_strncmp("pl ", file, 3))
		return (fill_plan(vars, file, obj));
	if (!ft_strncmp("co ", file, 3))
		return (fill_cone(vars, file, obj));
	return (-1);
}

int	assign_object(t_minirt *vars, char *file, t_object *obj)
{
	static int	err;
	static int	seen;

	ft_strcompress(file);
	if (!file[0] || *file == '#')
		return (free(obj), TRUE);
	err = parse_object_line(vars, file, obj, &seen);
	if (err == -1)
		return (cleanup(vars, 3), free(obj), throw_error(ERR), 0);
	if (err == 1)
		return (cleanup(vars, 3), free(obj), 0);
	if (err == 2)
		return (free(obj), TRUE);
	set_obj_vec(obj, obj->class);
	ft_lstadd_back(&vars->members, ft_lstnew(obj));
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

int	extract_data(t_minirt *vars, char *filename)
{
	int			i;
	int			fd;
	char		**file;

	vars->members = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open file"), FALSE);
	file = ft_read(fd, filename);
	i = 0;
	while (++i < 11)
		vars->cam[i].exist = 0;
	vars->selected.mouse = NO_CLICK;
	i = -1;
	while (file[++i])
		if (assign_object(vars, file[i], new_object()) == FALSE)
			return (close(fd), ft_free("2", file), FALSE);
	return (close(fd), ft_free("2", file), TRUE);
}
