/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:23 by sayed             #+#    #+#             */
/*   Updated: 2025/08/08 18:16:56 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int keyhook(int key, t_minirt *vars)
{
	if (key == 65307)
		quit(vars);
	if (ft_strchr("wasdqe", key) && vars->selected == 1)
		translation(vars, key);
	if (ft_strchr("wasdqe", key) && vars->selected == 2)
		rotation(vars, key);
    return (TRUE);
}

