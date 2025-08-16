/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:22:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 20:41:41 by aelsayed         ###   ########.fr       */
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

# define RTX "miniRT"
# define M_PI 3.14159265358979323846
# define M_WIDTH 1280
# define M_HEIGHT 720
# define M_THETA 0.76842396884
# define RAD 0.0174533
# define EPSILON 1e-3f
# define EPS_HIT 1e-3f
# define SHININESS 100.0f

/* **************************************** */
/*                 ENUMS                    */
/* **************************************** */

typedef enum e_type
{
	AMBIANCE,
	CAMERA,
	LIGHT,
	SPHERE,
	CYLINDER,
	PLANE,
	CONE,
	ERR = -1,
	TOO_MANY_CAM = -2,
	NO_AMB = -3
}	t_type;

typedef enum e_equation
{
	A,
	B,
	C,
	DELTA,
	SQRT
}	t_equation;

typedef enum e_mouse
{
	NO_CLICK,
	LEFT_CLICK,
	MIDDLE_CLICK,
	RIGHT_CLICK,
	SCROLL_DOWN,
	SCROLL_UP
}	t_mouse;

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

typedef enum e_mode
{
	NONE,
	SOLID,
	CHECKERED,
	BUMPMAP,
	TEXTURE
}	t_mode;

/* **************************************** */
/*             STRUCTURES                   */
/* **************************************** */

typedef struct s_window
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_win;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_texture
{
	t_mode	mode;
	void	*img;
	int		w;
	int		h;
	t_color	c1;
	t_color	c2;
}	t_texture;

typedef struct s_object
{
	int			class;
	float		ratio;
	float		angle;
	float		facing;
	float		r;
	float		h;
	float		shininess;
	t_vec3		p;
	t_vec3		n;
	t_vec3		o;
	t_vec3		tan;
	t_vec3		bitan;
	t_texture	t;
}	t_object;

typedef struct s_camera
{
	t_vec3	p;
	t_vec3	fw;
	t_vec3	rt;
	t_vec3	up;
	float	pitch;
	float	yaw;
	float	roll;
	float	fov;
	int		exist;
}	t_camera;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_select
{
	t_object	*obj;
	int			mouse;
	int			prev;
}	t_select;

typedef struct s_minirt
{
	t_win		win;
	// t_list		*members;
	t_object	**arr;
	t_camera	cam[11];
	int			cam_id;
	t_ray		**rays;
	float		plane_w;
	float		plane_h;
	float		amb_ratio;
	t_color		amb_rgb;
	int			amb;
	t_select	selected;
}	t_minirt;

typedef struct s_hit_info
{
	int			hit;
	t_vec3		poi;
	t_vec3		normal;
	t_color		color;
	float		light;
	double		dist;
	t_object	*obj;
}	t_hit_info;

typedef struct s_cyl
{
	t_object	*obj;
	t_vec3		origin;
	t_vec3		dir;
	t_vec3		base;
	t_vec3		axis;
}	t_cyl;

typedef struct s_hit
{
	t_hit_info	*best;
	float		*min_dist;
}	t_hit;

typedef t_hit_info	(*t_intersect)(t_vec3 origin, t_vec3 dir, t_object *obj);
typedef t_vec3		(*t_get_uv)(t_vec3 poi, t_object *obj);

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

/* init & data */
void		init_window(t_minirt *vars);
int			extract_data(t_minirt *vars, char *filename, t_list **list);
int			set_objects(t_minirt *vars, char *filename);
int			valid_filename(char *s);
float		ft_atof(char *str);
t_object	classifier(char *s, int *type, int class);
int			throw_error(int err, char strs[7][12]);
t_object	*new_object(void);
void		print_members(t_list *lst, void (*f)(t_object *));
void		print_data(t_object *obj);
t_texture	extract_texture(char *texture, t_minirt *vars);
int			split_3_parts(char *s, char p1[8], char p2[8], char p3[8]);
int			is_int(char *s);
t_object	*new_object(void);
int			assign_object(t_minirt *vars, char *file, \
	t_object *obj, t_list **list);
int			parse_object_line(t_minirt *vars, char *file, \
	t_object *obj, int *seen);

/* fillers */
int			fill_cone(t_minirt *vars, char *line, t_object *obj, char s[7][12]);
int			fill_plan(t_minirt *vars, char *data, t_object *obj, char s[7][12]);
int			fill_sphere(t_minirt *vars, char *data, t_object *obj, \
	char s[7][12]);
int			fill_cylinder(t_minirt *vars, char *data, t_object *obj, \
	char s[7][12]);
int			fill_light(char *data, t_object *obj, char s[7][12]);
int			fill_ambiance(char *data, t_minirt *vars, char s[7][12]);
int			fill_camera(char *data, t_minirt *vars, char s[7][12]);
int			fill_rgb(t_color *c, char p1[8], char p2[8], char p3[8]);
int			fill_float(float *f, char *s);
int			fill_vector(t_vec3 *v, char p[3][8], int class, int *type);

/* vectors */
float		dot(t_vec3 vec1, t_vec3 vec2);
t_vec3		cross(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec_op_vec(t_vec3 v1, t_vec3 v2, float (*op)(float, float));
t_vec3		sc_op_vec(float sc, t_vec3 v2, float (*op)(float, float));
float		distance(t_vec3 p1, t_vec3 p2);
t_vec3		init_vec(float x, float y, float z);
float		magnitude(t_vec3 vec);
t_vec3		normalize(t_vec3 vec);
float		add(float a, float b);
float		mul(float a, float b);
float		divis(float a, float b);
float		sub(float a, float b);

/* drawing */
void		put_pixel(t_minirt *vars, int x, int y, int color);

/* raytracing */
void		setup(t_minirt *vars, int cam_id);
void		raytracing(t_minirt *vars);
t_color		compute_lighting(t_hit_info hit, t_object *light, t_ray ray);
int			is_shaded(t_minirt *vars, t_hit_info hit, t_object *light);

/* debugging */
void		print_vec(t_vec3 vec, int nl);

/* transformations */
int			keyhook(int key, t_minirt *vars);
int			quit(t_minirt *vars);
void		hook_manipulation(t_minirt *vars);
int			mouse_click(int button, int x, int y, t_minirt *vars);
void		camera_translation(t_minirt *vars, int c);
void		camera_rotation(t_minirt *vars, int c);
void		resize_fov(t_minirt *vars);
void		translation(t_minirt *vars, int c);
void		rotation(t_minirt *vars, int c);
void		resize(t_minirt *vars);
void		shininess(t_minirt *vars, int key);

/* intersections */
t_hit_info	get_hit_info(t_vec3 origin, t_vec3 dir, t_minirt *vars);
t_hit_info	intersect_light(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *obj);
t_hit_info	intersect_cone(t_vec3 origin, t_vec3 dir, t_object *obj);

/* colors */
t_color		int_to_color(int in);
int			color_to_int(t_color color);
t_color		col_mul_col(t_color c1, t_color c2);
t_color		col_mul_sc(t_color col, float sc);
t_color		col_add_col(t_color c1, t_color c2);

/* textures */
t_color		get_color(t_vec3 poi, t_object *obj);
t_vec3		rotate_z(t_vec3 vec, float angle);
t_vec3		rotate_x(t_vec3 vec, float angle);
t_vec3		rotate_y(t_vec3 vec, float angle);
void		rotate(t_vec3 *vec, t_vec3 rot);
void		set_obj_vec(void *object, int type);
t_vec3		get_uv_cone(t_vec3 poi, t_object *obj);
t_vec3		get_uv_cylinder(t_vec3 poi, t_object *obj);
t_vec3		get_uv_plane(t_vec3 poi, t_object *obj);
t_vec3		get_uv_sphere(t_vec3 poi, t_object *obj);
#endif
