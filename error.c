/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 09:58:38 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	throw_error(int err)
{
	if (err == AMBIANCE)
		printfd(2, "Error\n\tUndefined data for Ambiant Light Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	if (err == CAMERA)
		printfd(2, "Error\n\tUndefined data for camera Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	if (err == LIGHT)
		printfd(2, "Error\n\tUndefined data for light Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	if (err == SPHERE)
		printfd(2, "Error\n\tUndefined data for sphere Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	if (err == CYLINDER)
		printfd(2, "Error\n\tUndefined data for cylinder Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	if (err == PLAN)
		printfd(2, "Error\n\tUndefined data for plan Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	if (err == 6)
		printfd(2, "Error\n\tUndefined data for  Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	return (1);
}
