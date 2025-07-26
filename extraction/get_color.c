/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:14:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/26 17:17:18 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	if (!parse_component(&str, &obj->rgb.r))
		return (FALSE);
	if (*str++ != ',')
		return (FALSE);
	if (!parse_component(&str, &obj->rgb.g))
		return (FALSE);
	if (*str++ != ',')
		return (FALSE);
	if (!parse_component(&str, &obj->rgb.b))
		return (FALSE);
	if (*str)
		return (FALSE);
	return (TRUE);
}
