/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 21:55:04 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/11 14:39:32 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		destroy_paths(t_vector *paths)
{
	size_t		i;

	i = -1;
	while (++i < paths->len)
		free(paths->arr[i].dirs);
	free(paths->arr);
}
