/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:38:41 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 15:56:29 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strcompress(char *str)
{
	char	(*src) = str;
	char	(*dst) = str;

	int (in_whitespace) = 0;
	while (src && *src)
	{
		if (ft_isspace((unsigned char)*src))
		{
			if (!in_whitespace)
			{
				*dst++ = ' ';
				in_whitespace = 1;
			}
		}
		else
		{
			*dst++ = *src;
			in_whitespace = 0;
		}
		src++;
	}
	if (dst > str && *(dst - 1) == ' ')
		dst--;
	*dst = '\0';
}
