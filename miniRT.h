/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:22:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 22:04:28 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* **************************************** */
/*                INCLUDES                  */
/* **************************************** */

# include "./libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "../minilibx/mlx.h"

/* **************************************** */
/*              DEFINITIONS                 */
/* **************************************** */

# define M "miniRT"
# define M_PI 3.14159265358979323846
# define M_WIDTH 1920
# define M_HEIGHT 1080
# define M_THETA 0.76842396884

/* **************************************** */
/*                 ENUMS                    */
/* **************************************** */

extern char	g_strs[7][12]; // for printing members

typedef enum e_type
{
	AMBIANCE,
	CAMERA,
	LIGHT,
	SPHERE,
	CYLINDER,
	PLAN,
	LAST_SHAPE,
	ERR = -1
}	t_type;

typedef enum e_token_type
{
	UNKNOWN,
	VECTOR,
	ORIENT,
	RGB,
	RGB1,
	RATIO,
	FOV,
	FLOAT
}	t_token_type;

/* **************************************** */
/*             STRUCTURES                   */
/* **************************************** */

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
	t_vec3	*crd;
	t_vec3	*n_vct;
	t_vec3	*o_vct;
	t_color	*rgb;
}			t_object;

typedef struct s_minirt
{
	t_win	win;
	t_list	*members;
}			t_minirt;

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

void		init_window(t_minirt *vars);
int			extract_data(t_minirt *vars, char *filename);
int			valid_filename(char *s);
float		ft_atof(char *str);
void		*classifier(char *s, int *type, int class);
int			throw_error(int err);
t_object	*new_object(void);
void		print_members(t_list *lst, void (*f)(t_object *));
void		print_data(t_object *obj);

//

// fillers
int			fill_plan(char *data, t_object *obj);
int			fill_sphere(char *data, t_object *obj);
int			fill_cylinder(char *data, t_object *obj);
int			fill_ambiance(char *data, t_object *obj);
int			fill_light(char *data, t_object *obj);
int			fill_camera(char *data, t_object *obj);
int			fill_rgb(t_color *c, char p1[8], char p2[8], char p3[8]);
int			fill_float(float *f, char *s);
int			fill_vector(t_vec3 *v, char p[3][8], int class, int *type);

#endif