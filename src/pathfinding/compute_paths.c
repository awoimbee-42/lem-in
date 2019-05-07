/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:07:33 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/08 01:18:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Hopefuly useless.
*/

static uint32_t	count_overlapping_paths(t_graph *g, t_vector *vec)
{
	uint32_t	i;
	int			j;
	uint32_t	nb_overlaps;

	nb_overlaps = 0;
	clean_graph_ants_mem(g);
	i = -1;
	while (++i < vec->len)
	{
		j = -1;
		while (vec->arr[i].dirs[++j] != g->end)
		{
			if (g->map.list[vec->arr[i].dirs[j]].ants != -1)
			{
				ft_printf("\nOVERLAP room %s\n", g->map.list[vec->arr[i].dirs[j]].name);
				// return (1);
				while (--j != -1)
					g->map.list[vec->arr[i].dirs[j]].ants = 0;
				++nb_overlaps;
				break ;
			}
			g->map.list[vec->arr[i].dirs[j]].ants = 1;
		}
	}
	ft_printf("%u overlaps\n", nb_overlaps);
	return (nb_overlaps);
}

void			compute_paths(t_graph *g, t_vector *vec, int nb_p)
{
	uint32_t	nb_paths_over;
	uint32_t	i;

	nb_paths_over = 0;
	graph_to_paths(g, vec);
	if ((nb_paths_over = calc_ants_to_launch(g, vec))
		|| (nb_paths_over = count_overlapping_paths(g, vec)))
	{
		ft_printf("TOO MANY PATHS / OVERLAP\n");
		clean_graph_everything(g);
		i = -1;
		while (++i < vec->len)
			free(vec->arr[i].dirs);
		vec->len = 0;
		edmonds_karp(g, vec, nb_p - nb_paths_over);
	}
}
