/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:16:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 11:59:43 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	init_vars(double *res, int *s, int *i, int *div)
// {
// 	*s = 1;
// 	*i = 0;
// 	*div = 1;
// 	*res = 0.0;
// }

// double	ft_atof(const char *str)
// {
// 	double	res;
// 	double	fract;
// 	int		sign;
// 	int		i;
// 	int		div;
// 	fract = 0.0;
// 	init_vars(&res, &sign, &i, &div);
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 		if (str[i++] == '-')
// 			sign = -1;
// 	while (str[i] && str[i] >= '0' && str[i] <= '9')
// 		res = res * 10.0 + (str[i++] - '0');
// 	if (str[i] == '.')
// 	{
// 		while (str[++i] && ft_isdigit(str[i]))
// 		{
// 			fract = fract * 10.0 + (str[i] - '0');
// 			div *= 10;
// 		}
// 	}
// 	return ((str[i] != '\0') * NAN + \
// 		(str[i] == '\0') * (sign * (res + fract / div)));
// }

double	ft_atof(const char *str)
{
	double	first_part;
	double	second_part;
	double	divisor;
	int		sign = 1;

	first_part = 0;
	second_part = 0;
	divisor = 1;
	if (str && (*str == '-' || *str == '+'))
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		first_part = first_part * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			second_part = second_part * 10 + (*str - '0');
			divisor *= 10;
			str++;
		}
	}
	return (first_part + (second_part / divisor));
}

void	print_data(t_object *obj)
{
	printf("\t class  : %s:%d\n", strs[obj->class], obj->class);
	printf("ratio    : %.1f\n", obj->ratio);
	printf("fov      : %.1f\n", obj->fov);
	printf("diameter : %.1f\n", obj->d);
	printf("height   : %.1f\n", obj->h);
	printf("rgb      : %d,%d,%d\n", obj->rgb.r, obj->rgb.g, obj->rgb.b);
	printf("crd      : %.1f,%.1f,%.1f\n", obj->crd.x, obj->crd.y, obj->crd.z);
	printf("n_nvt    : %.1f,%.1f,%.1f\n", obj->n_vct.x, obj->n_vct.y, obj->n_vct.z);
	printf("o_vct    : %.1f,%.1f,%.1f\n", obj->o_vct.x, obj->o_vct.y, obj->o_vct.z);
	printf("\n");
}

void	print_members(t_list *lst, void (*f)(t_object *))
{
	if (lst && f)
	{
		while (lst)
		{
			f((t_object *)lst->content);
			lst = lst->next;
		}
	}
}
