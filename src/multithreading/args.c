#include <miniRT.h>

void free_args(void **args)
{
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

void *mkargs(int count, ...)
{
	va_list	args;
	int		i;
	void	**arr;
	void	*ptr;

	arr = malloc(sizeof(void *) * count);
	if (!arr)
		return (NULL);
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(args, void *);
		arr[i] = ptr;
		i++;
	}
	va_end(args);
	return (arr);
}
