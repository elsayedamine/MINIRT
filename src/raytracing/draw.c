/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:30:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/30 16:31:25 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	put_pixel(t_minirt *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = vars->win.addr + (y * vars->win.line_length + x * \
			(vars->win.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
