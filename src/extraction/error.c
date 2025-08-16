/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/16 08:16:09 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	throw_error(int err, char strs[7][12])
{
	if (err <= CONE && err >= 0)
		printfd(2, "Error\n\tUndefined data for %s element!\n", strs[err]);
	if (err == ERR)
		printfd(2, "Error\n\tUndefined data entry!\n");
	if (err == TOO_MANY_CAM)
		printfd(2, "Error\n\tToo many cameras!\n");
	return (1);
}
