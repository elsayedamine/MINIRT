/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:20:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 20:44:58 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_object_line(t_minirt *vars, char *file, t_object *obj, int *seen)
{
	static char	strs[7][12] = {"AMBIANCE", "CAMERA", "LIGHT", \
	"SPHERE", "CYLINDER", "PLAN", "CONE"};

	if (!ft_strncmp("A ", file, 2) && !(*seen)++)
		return (fill_ambiance(file, vars, strs));
	if (!ft_strncmp("c ", file, 2))
		return (fill_camera(file, vars, strs));
	if (!ft_strncmp("l ", file, 2))
		return (fill_light(file, obj, strs));
	if (!ft_strncmp("sp ", file, 3))
		return (fill_sphere(vars, file, obj, strs));
	if (!ft_strncmp("cy ", file, 3))
		return (fill_cylinder(vars, file, obj, strs));
	if (!ft_strncmp("pl ", file, 3))
		return (fill_plan(vars, file, obj, strs));
	if (!ft_strncmp("co ", file, 3))
		return (fill_cone(vars, file, obj, strs));
	return (-1);
}

int	extract_data(t_minirt *vars, char *filename, t_list **list)
{
	int			i;
	int			fd;
	char		**file;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open file"), FALSE);
	file = ft_read(fd, filename);
	i = 0;
	while (++i < 11)
		vars->cam[i].exist = 0;
	vars->selected.mouse = NO_CLICK;
	vars->amb = 0;
	i = -1;
	while (file[++i])
	{
		if (assign_object(vars, file[i], new_object(), list) == FALSE)
			return (close(fd), ft_free("2", file), FALSE);
	}
	if (vars->amb == 0)
		return (throw_error(NO_AMB, NULL), FALSE);
	return (close(fd), ft_free("2", file), TRUE);
}

int	set_objects(t_minirt *vars, char *filename)
{
	int		i;
	int		size;
	t_list	*list;
	t_list	*curr;

	list = NULL;
	if (!extract_data(vars, filename, &list))
	{
		ft_lstclear(&list, free);
		return (0);
	}
	size = ft_lstsize(list);
	vars->arr = malloc(sizeof(t_object *) * (size + 1));
	vars->arr[size] = NULL;
	curr = list;
	i = 0;
	while (curr)
	{
		vars->arr[i] = malloc(sizeof(t_object));
		ft_memcpy(vars->arr[i++], curr->content, sizeof(t_object));
		curr = curr->next;
	}
	ft_lstclear(&list, free);
	return (1);
}
