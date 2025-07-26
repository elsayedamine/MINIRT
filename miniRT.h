/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:22:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 12:15:22 by aelsayed         ###   ########.fr       */
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
# include "minilibx/mlx.h"

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

extern char strs[7][12];

typedef enum e_type
{
	AMBIANCE,
	CAMERA,
	LIGHT,
	SPHERE,
	CYLINDER,
	PLAN,
	LAST_SHAPE
}           t_type;

typedef enum e_token_type {
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

# include "struct.h"

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

void		init_window(t_minirt *vars);
int			retrieve_data(t_minirt *vars, char *filename);
int			valid_filename(char *s);
double		ft_atof(const char *str);
void		*classifier(char *s, int *type);
int			throw_error(int err);
t_object	*new_object(void);
void		print_members(t_list *lst, void (*f)(t_object *));
void		print_data(t_object *obj);

//
//
int			fill_plan(t_minirt *vars, char *data, t_object *obj);
int			fill_sphere(t_minirt *vars, char *data, t_object *obj);
int			fill_cylinder(t_minirt *vars, char *data, t_object *obj);
int			fill_ambiance(t_minirt *vars, char *data, t_object *obj);
int			fill_light(t_minirt *vars, char *data, t_object *obj);
int			fill_camera(t_minirt *vars, char *data, t_object *obj);

#endif