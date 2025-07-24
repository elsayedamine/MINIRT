/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:22:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 23:12:13 by aelsayed         ###   ########.fr       */
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
	RGB,
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

void	init_window(t_minirt *vars);
int		retrieve_data(t_minirt *vars, char *filename);
int		valid_filename(char *s);
int	    fill_data(t_minirt *vars, char *data, int shape);
double	ft_atof(const char *str);
int	classifier(const char *s);


#endif