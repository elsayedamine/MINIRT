/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:22:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 16:36:39 by aelsayed         ###   ########.fr       */
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

//

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

#endif