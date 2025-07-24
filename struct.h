/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:35:25 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 17:01:40 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "miniRT.h"
typedef struct s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_win;

typedef struct s_parsing
{
	int		fd;
	char	**file;
}			t_pars;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			r2;
	int			g2;
	int			b2;
	int			r_interp;
	int			g_interp;
	int			b_interp;
}				t_color;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	z;
}			t_coord;

typedef struct s_ambiance
{
	int		ratio;
	t_color	rgb;
}			t_ambiance;

typedef struct s_camera
{
	t_coord	crd;
	t_coord	vct;
	float	fov;	
}			t_camera;

typedef struct s_light
{
	t_coord	crd;
	t_color	rgb;
	float	ratio;
}			t_light;

typedef struct s_settings
{
	t_ambiance	amb;
	t_camera	cam;
	t_light		light;	
}			t_settings;

typedef struct s_sphere
{
	t_coord	crd;
	float	d;
	t_color	rgb;
}			t_sphere;

typedef struct s_plan
{
	t_coord	crd;
	t_coord	vct;
	t_color	rgb;
}			t_plan;

typedef struct s_cylindre
{
	t_coord	crd;
	t_coord	vct;
	t_color	rgb;
	float	d;
	float	h;
}			t_cylinder;

typedef struct s_minirt
{
	t_win	win;
	t_pars	pars;
}			t_minirt;
 

#endif