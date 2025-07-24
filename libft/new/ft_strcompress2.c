/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcompress2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:27 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 15:56:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcompress2(char *str)
{
	const char	*src = str;
	char		*result;
	char		*dst;
	int			in_whitespace = 0;

	if (!str)
		return (NULL);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	dst = result;
	while (*src)
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
	if (dst > result && *(dst - 1) == ' ')
		dst--;
	*dst = '\0';
	return (result);
}
