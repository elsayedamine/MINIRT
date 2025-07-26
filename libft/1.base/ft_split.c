/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:30:44 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 09:47:50 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	allocator(char const *s, int row, char *set)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (ft_strchr(set, s[i]))
		i++;
	while (row--)
	{
		while (!ft_strchr(set, s[i]))
			i++;
		while (ft_strchr(set, s[i]) && s[i])
			i++;
	}
	while (!ft_strchr(set, s[i]) && s[i])
	{
		len++;
		i++;
	}
	return (len + 1);
}

static int	words(char const *s, char *set)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] && ft_strchr(set, s[i]))
		i++;
	while (s[i])
	{
		cnt++;
		while (s[i] && !ft_strchr(set, s[i]))
			i++;
		while (s[i] && ft_strchr(set, s[i]))
			i++;
	}
	return (cnt);
}

static char	*stricpy(char *dest, char const *src, char *set, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_strchr(set, src[j]))
		j++;
	while (index-- && src[j])
	{
		while (src[j] && !ft_strchr(set, src[j]))
			j++;
		while (src[j] && ft_strchr(set, src[j]))
			j++;
	}
	while (src[j] && !ft_strchr(set, src[j]))
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

static char	**check_free(char **arr, int i)
{
	if (!arr)
		return (NULL);
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
	return (arr);
}

char	**ft_split(char const *s, char *set)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (words(s, set) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words(s, set))
	{
		arr[i] = (char *)malloc(allocator(s, i, set));
		if (!arr[i])
			return (check_free(arr, i));
		i++;
	}
	i = 0;
	while (i < words(s, set))
	{
		arr[i] = stricpy(arr[i], s, set, i);
		i++;
	}
	arr[words(s, set)] = NULL;
	return (arr);
}
