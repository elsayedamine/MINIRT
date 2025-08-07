/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:42:47 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 17:29:51 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	throw_error(int err)
{
	if (err <= CONE && err >= 0)
		printfd(2, "Error\n\tUndefined data for %s Element!\n", g_strs[err]);
	if (err == ERR)
		printfd(2, "Error\n\tUndefined data Entry!\n");
	return (1);
}
