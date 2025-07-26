/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:16:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 21:57:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_vars(float *f, float *f1, float *f2, int *sign)
{
	*f = 0;
	*f1 = 0;
	*f2 = 1;
	*sign = 1;
}

float	ft_atof(char *str)
{
	float	first_part;
	float	second_part;
	float	divisor;
	int		sign;

	init_vars(&first_part, &second_part, &divisor, &sign);
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
	return (sign * (first_part + (second_part / divisor)));
}

void	print_data(t_object *obj)
{
	printf("\t class : %s:%d\n", g_strs[obj->class], obj->class);
	printf("ratio    : %.1f\n", obj->ratio);
	printf("fov      : %.1f\n", obj->fov);
	printf("diameter : %.1f\n", obj->d);
	printf("height   : %.1f\n", obj->h);
	if (obj->class != 1)
		printf("rgb      : %d,%d,%d\n", obj->rgb->r, obj->rgb->g, obj->rgb->b);
	if (obj->class != 0)
		printf("crd      : %.1f,%.1f,%.1f\n", obj->crd->x, \
			obj->crd->y, obj->crd->z);
	if (obj->class == PLAN)
		printf("n_nvt    : %.1f,%.1f,%.1f\n", \
			obj->n_vct->x, obj->n_vct->y, obj->n_vct->z);
	if (obj->class == CYLINDER || obj->class == CAMERA)
		printf("o_vct    : %.1f,%.1f,%.1f\n", \
			obj->o_vct->x, obj->o_vct->y, obj->o_vct->z);
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
