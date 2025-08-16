/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:29:26 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 10:40:06 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <time.h>

int	valid_filename(char *s)
{
	int	l;

	l = ft_strlen(s) - 1;
	if (l + 1 >= 4)
		return (ft_strncmp(&s[l - 2], ".rt", 3) == 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_minirt	vars;

	if (ac == 2 && valid_filename(av[1]))
	{
		if (!set_objects(&vars, av[1]))
			return (1);
		setup(&vars, 0);
		init_window(&vars);
		raytracing(&vars);
		hook_manipulation(&vars);
		return (0);
	}
	printfd(2, "Invalid Argument: Stop Playing Around\n");
	printfd(2, "\tExpected Format: ./miniRT <filename.rt>\n");
	return (1);
}
