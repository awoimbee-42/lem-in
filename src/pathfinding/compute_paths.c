/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:07:33 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/10 21:50:19 by awoimbee         ###   ########.fr       */
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
		ft_printf("{BLU}vec->arr[%u].dirs[0]: %s{eoc}\n", i, g->map.list[vec->arr[i].dirs[0]].name);
		while (vec->arr[i].dirs[++j] != g->end)
		{
			if (g->map.list[vec->arr[i].dirs[j]].ants != -1)
			{
				while (--j != -1)
					g->map.list[vec->arr[i].dirs[j]].ants = 0;
				free(vec->arr[i].dirs);
				vector_del_at(vec, i);
				--i;
				++nb_overlaps;
				break ;
			}
			g->map.list[vec->arr[i].dirs[j]].ants = 1;
		}
	}
	if (nb_overlaps)
		calc_ants_to_launch(g, vec);
	return (0);
	ft_printf("%u overlaps\n", nb_overlaps);
	return (nb_overlaps);
}

void			compute_paths(t_graph *g, t_vector *vec, int nb_p, int sup_po)
{
	uint32_t	nb_paths_over;
	uint32_t	i;

	nb_paths_over = 0;
	graph_to_paths(g, vec);
	if ((nb_paths_over = calc_ants_to_launch(g, vec))
		|| (nb_paths_over = count_overlapping_paths(g, vec)))
	{
		clean_graph_everything(g);
		i = -1;
		while (++i < vec->len)
			free(vec->arr[i].dirs);
		vec->len = 0;
		edmonds_karp(g, vec, nb_p - nb_paths_over, sup_po);
	}
}
