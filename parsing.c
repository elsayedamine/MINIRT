/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 23:59:11 by aelsayed         ###   ########.fr       */
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
t_object	*new_object(void);
int	retrieve_data(t_minirt *vars, char *filename)
{
	char	**file;
	int		err;

	vars->pars.fd = open(filename, O_RDONLY);
	if (vars->pars.fd == -1)
		return (perror("Failed to open file"), FALSE);
	vars->pars.file = ft_read(vars->pars.fd, filename);
	file = vars->pars.file;
	int	i = -1;
	err = 0;
	while (file[++i])
	{
		ft_strcompress(file[i]);
		if (!file[i][0])
			continue ;
		if (!ft_strncmp("A ", file[i], 2))
			err = fill_ambiance(vars, file[i], new_object());
		else if (!ft_strncmp("C ", file[i], 2))
			err = fill_camera(vars, file[i], new_object());
		else if (!ft_strncmp("L ", file[i], 2))
			err = fill_light(vars, file[i], new_object());
		else if (!ft_strncmp("sp ", file[i], 3))
			err = fill_sphere(vars, file[i], new_object());
		else if (!ft_strncmp("cy ", file[i], 3))
			err = fill_cylinder(vars, file[i], new_object());
		else if (!ft_strncmp("pl ", file[i], 3))
			err = fill_plan(vars, file[i], new_object());
		else
			return (FALSE);
		if (err)
			return (FALSE);
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
	return (obj); 
}

int	fill_ambiance(t_minirt *vars, char *data, t_object *obj)
{
	char	**fields;
	int		i;
	int		type;

	type = UNKNOWN;
	fields = ft_split(data, WHITE);
	if (fields && fields[1])
		type = classifier(fields[1]);
	if (type == RATIO)
		// obj->ratio = ;
	return (0);
}
