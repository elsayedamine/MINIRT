/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:16:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/24 22:55:50 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_vars(double *res, int *s, int *i, int *div)
{
	*s = 1;
	*i = 0;
	*div = 1;
	*res = 0.0;
}

double	ft_atof(const char *str)
{
	double	res;
	double	fract;
	int		sign;
	int		i;
	int		div;

	fract = 0.0;
	init_vars(&res, &sign, &i, &div);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		while (str[++i] && ft_isdigit(str[i]))
		{
			fract = fract * 10.0 + (str[i] - '0');
			div *= 10;
		}
	}
	return ((str[i] != '\0') * NAN + \
		(str[i] == '\0') * (sign * (res + fract / div)));
}
