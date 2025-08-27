/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 23:28:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/26 16:39:41 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_color	get_pixel_bump(int x, int y, void *img)
{
	int		endian;
	int		sl;
	int		bpp;
	int		offset;
	char	*addr;

	addr = mlx_get_data_addr(img, &bpp, &sl, &endian);
	offset = y * sl + x * (bpp / 8);
	return (int_to_color(*(unsigned int *)(addr + offset)));
}

t_color	get_pixel_checkered(float x, float y, t_texture texture)
{
	float	tile_size;
	int		u;
	int		v;

	tile_size = texture.w / 100.0f;
	u = (int)floor(x / tile_size);
	v = (int)floor(y / tile_size);
	if ((u + v) % 2 == 0)
		return (texture.c1);
	else
		return (texture.c2);
}

t_color	get_color(t_vec3 poi, t_object *obj)
{
	t_vec3			uv;
	int				x;
	int				y;
	static t_get_uv	f[5] = {
		get_uv_sphere,
		get_uv_cylinder,
		get_uv_plane,
		get_uv_cone,
		get_uv_rectangle
	};

	if (obj->t.mode == NONE)
		return (obj->t.c1);
	uv = f[obj->class - 3](poi, obj);
	if (obj->t.mode == CHECKERED)
		return (get_pixel_checkered(uv.x, uv.y, obj->t));
	x = (1.0f - uv.x) * (float)(obj->t.w - 1);
	y = uv.y * (float)(obj->t.h - 1);
	x = (x > 0) * x;
	y = (y > 0) * y;
	if (obj->t.mode == BUMPMAP)
		return (get_pixel_bump(x, y, obj->t.img));
	return (obj->t.c1);
}
