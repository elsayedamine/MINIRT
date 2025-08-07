/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:22:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/31 16:02:11 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* **************************************** */
/*                INCLUDES                  */
/* **************************************** */

# include <libft.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>

/* **************************************** */
/*              DEFINITIONS                 */
/* **************************************** */

# define M "miniRT"
# define M_PI 3.14159265358979323846
# define M_WIDTH 1920
# define M_HEIGHT 1080
# define M_THETA 0.76842396884
# define RAD 0.0174533
# define EPSILON 0.0001f

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
	CONE,
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
	float	angle;
	float	r;
	float	h;
	t_vec3	p;
	t_vec3	n;
	t_vec3	o;
	t_color	rgb;
}			t_object;

typedef struct s_camera
{
	t_vec3	p;
	t_vec3	fw;
	t_vec3	rt;
	t_vec3	up;	
	float	fov;
}			t_camera;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 dir;
} t_ray;

typedef struct s_minirt
{
	t_win	win;
	t_list	*members;
	t_camera cam;
	t_ray	**rays;
	float	plane_w;
	float	plane_h;
	float	amb_ratio;
	t_color	amb_rgb;
}			t_minirt;

typedef struct s_hit_info
{
	int		hit;
	t_vec3	poi;
	t_vec3	normal;
	t_color	color;
	float	light;
	double	dist;
	t_object *obj;

}		t_hit_info;

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

void		init_window(t_minirt *vars);
int			extract_data(t_minirt *vars, char *filename);
int			valid_filename(char *s);
float		ft_atof(char *str);
t_object	classifier(char *s, int *type, int class);
int			throw_error(int err);
t_object	*new_object(void);
void		print_members(t_list *lst, void (*f)(t_object *));
void		print_data(t_object *obj);
void		cleanup(t_minirt *vars, int n);

//

// fillers
int			fill_plan(char *data, t_object *obj);
int			fill_sphere(char *data, t_object *obj);
int			fill_cylinder(char *data, t_object *obj);
int			fill_ambiance(char *data, t_minirt *vars);
int			fill_light(char *data, t_object *obj);
int			fill_camera(char *data, t_minirt *vars);
int			fill_rgb(t_color *c, char p1[8], char p2[8], char p3[8]);
int			fill_float(float *f, char *s);
int			fill_vector(t_vec3 *v, char p[3][8], int class, int *type);

// vectors
float dot(t_vec3 vec1, t_vec3 vec2);
t_vec3 cross(t_vec3 vec1, t_vec3 vec2);
t_vec3 vec_op_vec(t_vec3 vec1, t_vec3 vec2, float (*op)(float, float));
t_vec3 sc_op_vec(float sc, t_vec3 vec2, float (*op)(float, float));
float	distance(t_vec3 p1, t_vec3 p2);
t_vec3	init_vec(float x, float y, float z);
float magnitude(t_vec3 vec);
t_vec3 normalize(t_vec3 vec);
float add(float a, float b);
float mul(float a, float b);
float divis(float a, float b);
float sub(float a, float b);

//drawing
void	put_pixel(t_minirt *vars, int x, int y, int color);

//raytracing
void setup(t_minirt *vars);
void raytracing(t_minirt *vars);

//debugging
void print_vec(t_vec3 vec, int nl);

// key_hooks
int keyhook(int key, t_minirt *vars);
int	quit(t_minirt *vars);
void    hook_manipulation(t_minirt *vars);

// intersections
typedef t_hit_info (*t_intersect)(t_vec3 origin, t_vec3 dir, t_object *obj);

t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_last_shape(t_vec3 origin, t_vec3 dir, t_object *obj);

// colors
t_color init_color(int r, int g, int b);
t_color int_to_color(int in);
int color_to_int(t_color color);
t_color col_mul_col(t_color c1, t_color c2);
t_color col_mul_sc(t_color col, float sc);
t_color col_add_col(t_color c1, t_color c2);

#endif