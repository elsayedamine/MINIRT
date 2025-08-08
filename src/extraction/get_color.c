/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnxrly <gnxrly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:14:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/08 18:16:25 by gnxrly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_component(char **str, int *component)
{
	int	value;
	int	len;

	value = 0;
	len = 0;
	if (!*str || !ft_isdigit(**str))
		return (FALSE);
	while (**str && ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
		len++;
	}
	if (value < 0 || value > 255 || len > 3)
		return (FALSE);
	*component = value;
	return (TRUE);
}

int	get_rgb(t_minirt *vars, char *str, t_object *obj)
{
	(void)vars;
	if (!parse_component(&str, &obj->t.c1.r))
		return (FALSE);
	if (*str++ != ',')
		return (FALSE);
	if (!parse_component(&str, &obj->t.c1.g))
		return (FALSE);
	if (*str++ != ',')
		return (FALSE);
	if (!parse_component(&str, &obj->t.c1.b))
		return (FALSE);
	if (*str)
		return (FALSE);
	return (TRUE);
}
