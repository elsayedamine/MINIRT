/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:48:09 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/25 18:18:19 by aelsayed         ###   ########.fr       */
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
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;
typedef struct s_class
{
	int		class;
	void	*data;
}			t_class;
typedef struct s_object
{
	int		class;
	float	ratio;
	float	fov;
	float	d;	
	float	h;
	t_color	rgb;
	t_vec3	crd;
	t_vec3	n_vct;
	t_vec3	o_vct;
}			t_object;

typedef struct s_minirt
{
	t_win	win;
	t_pars	pars;
	t_list	*members;
}			t_minirt;
 

#endif

