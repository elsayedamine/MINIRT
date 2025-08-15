/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:09:41 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:09:46 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	print_vec(t_vec3 vec, int nl)
{
	printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
	if (nl)
		putchar('\n');
}

void	print_data(t_object *obj)
{
	printf("\t class : %s:%d\n", g_strs[obj->class], obj->class);
	printf("ratio    : %.1f\n", obj->ratio);
	printf("angle      : %.1f\n", obj->angle);
	printf("diameter : %.1f\n", obj->r);
	printf("height   : %.1f\n", obj->h);
	if (obj->class != 1)
		printf("rgb      : %d,%d,%d\n", obj->t.c1.r, obj->t.c1.g, obj->t.c1.b);
	if (obj->class != 0)
		printf("crd      : %.1f,%.1f,%.1f\n", obj->p.x, \
			obj->p.y, obj->p.z);
	if (obj->class == PLANE)
		printf("n_nvt    : %.1f,%.1f,%.1f\n", \
			obj->n.x, obj->n.y, obj->n.z);
	if (obj->class == CYLINDER || obj->class == CAMERA)
		printf("o    : %.1f,%.1f,%.1f\n", \
			obj->o.x, obj->o.y, obj->o.z);
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
