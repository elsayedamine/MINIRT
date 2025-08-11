#include <miniRT.h>

void free_args(void **args)
{
	void **cpy;

	cpy = args;
	while (*cpy)
		free(*cpy++);
	free(args);
}

void *get_args(void *args)
{
	static void **index;
	void *ret;

	if (args)
		index = (void **)args;
	ret = *index;
	if (ret)
		index++;
	return (ret);
}
void *mk_args(int count, ...)
{
	va_list	args;
	int		i;
	void	**arr;
	int		size;
	void	*ptr;

	arr = malloc(sizeof(void *) * (count + 1));
	if (!arr)
		return (NULL);
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(args, void *);
		size = va_arg(args, unsigned long);
		arr[i] = malloc(size);
		ft_memcpy(arr[i], ptr, size);
		i++;
	}
	arr[i] = NULL;
	va_end(args);
	return (arr);
}
