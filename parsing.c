/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 17:12:03 by aelsayed         ###   ########.fr       */
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
		if (file[i][0] == 'A' && file[i][1] == ' ')
			err += fill_ambiance(vars, file[i]);
		if (file[i][0] == 'C' && file[i][1] == ' ')
			err += fill_camera(vars, file[i]);
		if (file[i][0] == 'L' && file[i][1] == ' ')
			err += fill_light(vars, file[i]);
		if (!ft_strncmp("sp ", file[i], 3))
			err += fill_sphere(vars, file[i]);
		if (!ft_strncmp("cy ", file[i], 3))
			err += fill_cylinder(vars, file[i]);
		if (!ft_strncmp("pl ", file[i], 3))
			err += fill_plan(vars, file[i]);
	}
	close(vars->pars.fd);
	return (TRUE);
}

int	fill_ambiance(t_minirt *vars, char *data)
{
	char	*split
}