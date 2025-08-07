#include <miniRT.h>

void print_vec(t_vec3 vec, int nl)
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
		printf("rgb      : %d,%d,%d\n", obj->rgb.r, obj->rgb.g, obj->rgb.b);
	if (obj->class != 0)
		printf("crd      : %.1f,%.1f,%.1f\n", obj->p.x, \
			obj->p.y, obj->p.z);
	if (obj->class == PLAN)
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
