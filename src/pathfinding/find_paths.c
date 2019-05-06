/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/06 15:28:26 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		bfs(t_graph *g, uint32_t *parents, t_queue *q)
{
	uint32_t	node;
	uint32_t	tmp;
	uint32_t	tmp_lnk;

	if (!que_push(q, g->start))
		exit_lem_in("Could not create queue, bfs cannot continue");
	while (!que_isempty(q))
	{
		node = que_pop(q);
		tmp = -1;
		while (++tmp < g->map.list[node].nb_link)
		{
			tmp_lnk = g->map.list[node].links[tmp];
			if (!(tmp_lnk & LNK_VISITED) && parents[tmp_lnk] == (uint32_t)-1
				&& (!g->map.list[node].ants
					|| (int)tmp_lnk == g->map.list[node].ants))
			{
				parents[tmp_lnk] = node;
				if (tmp_lnk == g->end)
					return (1);
				que_push(q, tmp_lnk);
			}
		}
	}
	return (0);
}

void			edmonds_karp(t_graph *g, t_vector *paths, uint32_t max_paths)
{
	t_queue		*q;
	uint32_t	*parents;
	uint32_t	nb_paths;
	uint32_t	i;

	q = que_new(g->map.used);
	parents = malloc(g->map.used * sizeof(uint32_t));
	nb_paths = -1;
	while (++nb_paths < max_paths)
	{
		ft_mem32set(parents, -1, g->map.used);
		que_flush(q);
		if (!bfs(g, parents, q))
			break ;
		write_path(g, parents);
	}
	que_destroy(q);
	free(parents);
	i = -1;
	while (++i < g->map.used)
		g->map.list[i].ants = 0;
	compute_paths(g, paths, nb_paths);
}

void			find_paths(t_graph *graph, t_str *str)
{
	t_vector	paths;

	if (!vector_init(&paths, 10))
		exit_lem_in("Cannot allocate memory for paths vector");
	edmonds_karp(graph, &paths, 99999);
	if (paths.len == 0)
		exit_clean(graph, 1);
	display_t_str(str);
	send_ants(graph, &paths);
}
