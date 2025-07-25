/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/25 19:07:14 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	throw_error(int err)
{
	if (err == AMBIANCE)
		printfd(2, "Error\n\tUndefined data for Ambiant Light Element!\n\tExpected Entry: A ratio(x.x) rgb_color(x.x.x)\n");
	return (1);
}
