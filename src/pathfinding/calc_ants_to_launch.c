/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ants_to_launch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:11:16 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/13 16:58:27 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Calculates, for each path, the ideal number of ants to launch.
**	If the mathematiccal function says that we should send a negative number of
**		ants it means that we have too many paths.
*/

static uint		get_paths_len_sum(t_vector *paths)
{
	size_t		i;
	uint		paths_len;

	i = -1;
	paths_len = 0;
	while (++i < paths->len)
		paths_len += paths->arr[i].len;
	return (paths_len);
}

static void		dispatch_remaining_ants(int tot, int launched, t_vector *paths)
{
	int			delta_ants;
	int			i;

	delta_ants = tot - launched;
	if (delta_ants > 0)
	{
		i = -1;
		while (++i < (int)paths->len && delta_ants != 0)
		{
			paths->arr[i].ants_to_lanch += 1;
			delta_ants -= 1;
		}
	}
	else if (delta_ants < 0)
	{
		i = paths->len;
		while (--i != -1 && delta_ants != 0)
		{
			paths->arr[i].ants_to_lanch -= 1;
			delta_ants += 1;
		}
	}
}

static int		superfluous_paths(t_vector *vec)
{
	uint		i;

	i = -1;
	while (++i < vec->len)
	{
		if (vec->arr[i].ants_to_lanch < 0)
			return (vec->len - i);
	}
	return (0);
}

int				calc_ants_to_launch(t_graph *g, t_vector *vec)
{
	uint		i;
	uint		paths_len_sum;
	int			ants_launched;

	ants_launched = 0;
	paths_len_sum = get_paths_len_sum(vec);
	i = -1;
	while (++i < vec->len)
	{
		vec->arr[i].ants_to_lanch = ((int)g->ants
				- (((int)vec->len - 1) * (int)vec->arr[i].len
					- ((int)paths_len_sum - (int)vec->arr[i].len)))
			/ (int)vec->len;
		ants_launched += vec->arr[i].ants_to_lanch;
	}
	dispatch_remaining_ants((int)g->ants, ants_launched, vec);
	return (superfluous_paths(vec));
}
