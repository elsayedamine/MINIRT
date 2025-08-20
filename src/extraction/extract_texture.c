/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:11:44 by sayed             #+#    #+#             */
/*   Updated: 2025/08/15 16:08:33 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_texture	extract_checker(char *texture)
{
	t_texture	t;
	char		**colors;
	char		p[3][8];

	t.mode = CHECKERED;
	t.img = NULL;
	if (texture[ft_strlen(texture) - 1] == '-')
		return (t.mode = NONE, t);
	colors = ft_split(texture + 8, "-");
	if (!colors || ft_arrlen(colors) > 3 || \
		!is_int(colors[0]) || ft_atoi(colors[0]) <= 0)
		return (ft_free("2", colors), t.mode = NONE, t);
	if (!split_3_parts(colors[1], p[0], p[1], p[2]) || \
			fill_rgb(&t.c1, p[0], p[1], p [2]) != 3)
		return (ft_free("2", colors), t.mode = NONE, t);
	if (!split_3_parts(colors[2], p[0], p[1], p[2]) || \
		fill_rgb(&t.c2, p[0], p[1], p[2]) == 5)
		return (ft_free("2", colors), t.mode = NONE, t);
	return (t.w = ft_atoi(colors[0]), ft_free("2", colors), t);
}

t_texture	extract_texture(char *texture, t_minirt *vars)
{
	t_texture	t;

	if (!ft_strncmp("bump=", texture, 5) && \
		!ft_strncmp(&texture[ft_strlen(texture) - 4], ".xpm", 4))
	{
		t.mode = BUMPMAP;
		t.img = mlx_xpm_file_to_image(vars->win.mlx, texture + 5, &t.w, &t.h);
		if (!t.img)
			return (t.mode = NONE, t);
		return (t);
	}
	if (!ft_strncmp("checker=", texture, 8))
		return (extract_checker(texture));
	return (t.mode = NONE, t);
}
