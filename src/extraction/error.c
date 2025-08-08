/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/09 00:04:27 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	throw_error(int err)
{
	if (err <= CONE && err >= 0)
		printfd(2, "Error\n\tUndefined data for %s Element !\n", g_strs[err]);
	if (err == ERR)
		printfd(2, "Error\n\tUndefined data Entry !\n");
	if (err == TOO_MANY_CAM)
		printfd(2, "Too ManY Cameras !\n");
	return (1);
}
