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
		printfd(2, "Error\n\tUndefined data for %s element!\n", g_strs[err]);
	if (err == ERR)
		printfd(2, "Error\n\tUndefined data entry!\n");
	if (err == TOO_MANY_CAM)
		printfd(2, "Error\n\tToo many cameras!\n");
	return (1);
}
