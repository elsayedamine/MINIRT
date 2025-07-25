/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/25 19:04:05 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	valid_filename(char *s)
{
	int	l;

	l = ft_strlen(s) - 1;
	if (l + 1 >= 4)
	{
		if (!ft_strncmp(&s[l - 2], ".rt", 3))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	retrieve_data(t_minirt *vars, char *filename)
{
	char		**file;
	int			err;
	int			i;
	t_object	*obj;
	vars->members = NULL;

	vars->pars.fd = open(filename, O_RDONLY);
	if (vars->pars.fd == -1)
		return (perror("Failed to open file"), FALSE);
	vars->pars.file = ft_read(vars->pars.fd, filename);
	file = vars->pars.file;
	i = -1;
	err = 0;
	while (file[++i])
	{
		ft_strcompress(file[i]);
		obj = new_object();
		if (!file[i][0])
			continue ;
		if (!ft_strncmp("A ", file[i], 2))
			err = fill_ambiance(vars, file[i], obj);
		else if (!ft_strncmp("C ", file[i], 2))
			err = fill_camera(vars, file[i], obj);
		else if (!ft_strncmp("L ", file[i], 2))
			err = fill_light(vars, file[i], obj);
		else if (!ft_strncmp("sp ", file[i], 3))
			err = fill_sphere(vars, file[i], obj);
		else if (!ft_strncmp("cy ", file[i], 3))
			err = fill_cylinder(vars, file[i], obj);
		else if (!ft_strncmp("pl ", file[i], 3))
			err = fill_plan(vars, file[i], obj);
		else
			return (free(obj), ft_lstclear(&vars->members, free), FALSE);
		if (err)
			return (ft_lstclear(&vars->members, free), FALSE);
		ft_lstadd_back(&vars->members, ft_lstnew(obj));
	}
	close(vars->pars.fd);
	return (TRUE);
}

t_object	*new_object(void)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL); // cleanup
	obj->class = -1;
	obj->d = -2.0;
	obj->fov = -2.0;
	obj->h = -2.0;
	obj->ratio = -2.0;
	return (obj); 
}

