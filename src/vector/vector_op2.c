/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:46 by aelsayed          #+#    #+#             */
/*   Updated: 2025/08/15 17:29:01 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_vec3	init_vec(float x, float y, float z)
{
	t_vec3	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

float	magnitude(t_vec3 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_vec3	normalize(t_vec3 vec)
{
	float	mag;

	mag = magnitude(vec);
	vec.x /= mag;
	vec.y /= mag;
	vec.z /= mag;
	return (vec);
}
