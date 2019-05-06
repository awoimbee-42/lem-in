/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ants_to_launch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:11:16 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/05 19:58:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Calculates, for each path, the ideal number of ants to launch.
**	If the mathematiccal function says that we should send a negative number of
**		ants it means that we have too many paths.
*/

static uint32_t	get_paths_len_sum(t_vector *paths)
{
	size_t		i;
	uint32_t	paths_len;

	i = -1;
	paths_len = 0;
	while (++i < paths->len)
		paths_len += paths->arr[i].len;
	return (paths_len);
}

static void		dispatch_remaining_ants(int tot, int launched, t_vector *paths)
{
	int			delta_ants;
	int			step;
	size_t		i;

	delta_ants = tot - launched;
	step = delta_ants > 0 ? 1 : -1;
	i = -1;
	while (++i < paths->len && delta_ants != 0)
	{
		paths->arr[i].ants_to_lanch += step;
		delta_ants -= step;
	}
}

int				calc_ants_to_launch(t_graph *g, t_vector *vec)
{
	uint32_t	i;
	uint32_t	paths_len_sum;
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
		if (vec->arr[i].ants_to_lanch < 0)
			return (vec->len - i);
	}
	dispatch_remaining_ants((int)g->ants, ants_launched, vec);
	return (0);
}
