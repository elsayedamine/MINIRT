/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/07 23:59:12 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_object	*new_object(void)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->class = -1;
	obj->angle = -1;
	obj->r = -2.0;
	obj->h = -2.0;
	obj->ratio = -2.0;
	return (obj);
}

int	assign_object(t_minirt *vars, char *file, t_object *obj)
{
	static int		err = 0;
	static int	seen[2];

	ft_strcompress(file);
	if (!file[0])
		return (free(obj), TRUE);
	if (!ft_strncmp("A ", file, 2) && !seen[0]++)
		err = fill_ambiance(file, vars);
	else if (!ft_strncmp("C ", file, 2) && !seen[1]++)
		err = fill_camera(file, vars);
	else if (!ft_strncmp("l ", file, 2))
		err = fill_light(file, obj);
	else if (!ft_strncmp("sp ", file, 3))
		err = fill_sphere(vars, file, obj);
	else if (!ft_strncmp("cy ", file, 3))
		err = fill_cylinder(vars, file, obj);
	else if (!ft_strncmp("pl ", file, 3))
		err = fill_plan(vars, file, obj);
	else if (!ft_strncmp("co ", file, 3))
		err = fill_cone(vars, file, obj);
	else if (*file == '#')
		return (free(obj), 1);
	else
		return (cleanup(vars, 3), free(obj), throw_error(ERR), 0);
	if (err == 1)
		return (cleanup(vars, 3), free(obj), 0);
	if (err == 2)
		return (free(obj), TRUE);
	return (ft_lstadd_back(&vars->members, ft_lstnew(obj)), 1);
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
	while (file[i])
	{
		// printf("%s\n", file[i]);
		if (assign_object(vars, file[i++], new_object()) == FALSE)
			return (close(fd), ft_free("2", file), FALSE);
	}
	return (close(fd), ft_free("2", file), TRUE);
}

void	cleanup(t_minirt *vars, int n)
{
	if (1 & n)
		ft_lstclear(&vars->members, free);
	// if (4 & n)
		//
	// if (8 & n)
		//
}
