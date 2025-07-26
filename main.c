/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:29:26 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 11:14:38 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	strs[7][12] = {"AMBIANCE", "CAMERA", "LIGHT", "SPHERE", "CYLINDER", "PLAN", "LAST_SHAPE"};

int main(int ac, char **av)
{
	t_minirt	vars;

	if (ac == 2 && valid_filename(av[1]))
	{
		if (retrieve_data(&vars, av[1]) == FALSE)
			return (3);
		init_window(&vars);
		// rendering(&vars, &parser);
		return (0);
	}
	printfd(2, "Invalid Argument: Stop Playing Around\n");
	printfd(2, "\tExpected Format: ./miniRT <filename.rt>\n");
}
