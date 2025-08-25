/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/25 18:19:00 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	throw_error(int err, char strs[8][12])
{
	if (err <= RECTANGLE && err >= 0)
		printfd(2, "Error\n\tUndefined data for %s element!\n", strs[err]);
	if (err == ERR)
		printfd(2, "Error\n\tUndefined data entry!\n");
	if (err == TOO_MANY_CAM)
		printfd(2, "Error\n\tToo many cameras!\n");
	if (err == NO_AMB)
		printfd(2, "Error\n\tNo ambiant lighting data!\n");
	return (1);
}
