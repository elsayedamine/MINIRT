/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcompress2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:27 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 17:27:50 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	compress_whitespace(char *src, char *dst)
{
	int	in_whitespace;

	in_whitespace = 0;
	while (*src)
	{
		if (ft_isspace((unsigned char)*src))
		{
			if (!in_whitespace)
				*dst++ = ' ';
			in_whitespace = 1;
		}
		else
		{
			*dst++ = *src;
			in_whitespace = 0;
		}
		src++;
	}
	if (dst > src && *(dst - 1) == ' ')
		dst--;
	*dst = '\0';
}

char	*ft_strcompress2(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	compress_whitespace(str, result);
	return (result);
}
