/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 22:39:22 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_object	*new_object(void)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->class = -1;
	obj->d = -2.0;
	obj->fov = -2.0;
	obj->h = -2.0;
	obj->ratio = -2.0;
	obj->n_vct = NULL;
	obj->o_vct = NULL;
	obj->rgb = NULL;
	obj->crd = NULL;
	return (obj);
}

int	assign_object(t_minirt *vars, char *file, t_object *obj)
{
	int			err;
	static int	seen[3];

	err = 0;
	ft_strcompress(file);
	if (!file[0])
		return (TRUE);
	if (!ft_strncmp("A ", file, 2) && !seen[0]++)
		err = fill_ambiance(file, obj);
	else if (!ft_strncmp("C ", file, 2) && !seen[1]++)
		err = fill_camera(file, obj);
	else if (!ft_strncmp("L ", file, 2) && !seen[2]++)
		err = fill_light(file, obj);
	else if (!ft_strncmp("sp ", file, 3))
		err = fill_sphere(file, obj);
	else if (!ft_strncmp("cy ", file, 3))
		err = fill_cylinder(file, obj);
	else if (!ft_strncmp("pl ", file, 3))
		err = fill_plan(file, obj);
	else
		return (ft_lstclear(&vars->members, free), throw_error(ERR), FALSE);
	if (err)
		return (ft_lstclear(&vars->members, free), FALSE);
	return (ft_lstadd_back(&vars->members, ft_lstnew(obj)), TRUE);
}

int	extract_data(t_minirt *vars, char *filename)
{
	int			i;
	int			fd;
	char		**file;
	t_object	*obj;

	vars->members = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open file"), FALSE);
	file = ft_read(fd, filename);
	i = 0;
	while (file[i])
	{
		obj = new_object();
		if (assign_object(vars, file[i++], obj) == FALSE)
			return (close(fd), free_objects(obj), ft_free("2", file), FALSE);
	}
	return (close(fd), ft_free("2", file), TRUE);
}
