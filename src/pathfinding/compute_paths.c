/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:07:33 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/11 14:58:35 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		delete_path(t_graph *g, t_vector *paths, uint path, int i)
{
	while (--i != -1)
		g->map.list[paths->arr[path].dirs[i]].ants = 0;
	free(paths->arr[path].dirs);
	vector_del_at(paths, path);
}

/*
**	Hopefuly useless.
**	Paths are already sorted in ascending order,
**	So we just have to write them one by one and if a path overlaps with
**		a previous one, we simply remove it.
*/

static uint		count_overlapping_paths(t_graph *g, t_vector *vec)
{
	uint		i;
	int			j;
	uint		overlaps;

	overlaps = 0;
	clean_graph_ants_mem(g);
	i = -1;
	while (++i < vec->len)
	{
		j = -1;
		while (vec->arr[i].dirs[++j] != g->end)
		{
			if (g->map.list[vec->arr[i].dirs[j]].ants != -1)
			{
				delete_path(g, vec, i, j);
				--i;
				overlaps = 1;
				break ;
			}
			g->map.list[vec->arr[i].dirs[j]].ants = 1;
		}
	}
	if (overlaps)
		calc_ants_to_launch(g, vec);
	return (0);
}

void			compute_paths(t_graph *g, t_vector *vec, int nb_p, int sup_po)
{
	uint		nb_paths_over;
	uint		i;

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
