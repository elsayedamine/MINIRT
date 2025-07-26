/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:29:26 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 17:30:19 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	g_strs[7][12] = {"AMBIANCE", "CAMERA", "LIGHT", \
	"SPHERE", "CYLINDER", "PLAN", "LAST_SHAPE"}; // only for printing

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

int	main(int ac, char **av)
{
	t_minirt	vars;

	if (ac == 2 && valid_filename(av[1]))
	{
		if (extract_data(&vars, av[1]) == FALSE)
			return (130);
		print_members(vars.members, print_data);
		// init_window(&vars);
		// rendering(&vars, &parser);
		return (0);
	}
	printfd(2, "Invalid Argument: Stop Playing Around\n");
	printfd(2, "\tExpected Format: ./miniRT <filename.rt>\n");
}
