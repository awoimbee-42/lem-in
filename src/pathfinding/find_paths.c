/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/11 14:48:00 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	mem_link is used as an indicator that we are 'going upstream',
**		erasing another path
*/

static int		bfs(t_graph *g, uint *parents, t_queue *q, int superpo)
{
	uint		node;
	uint		tmp;
	uint		tmp_lnk;

	if (!que_push(q, g->start))
		exit_lem_in("Could not create queue, bfs cannot continue");
	parents[g->start] = -2;
	while (!que_isempty(q))
	{
		node = que_pop(q);
		if (g->map.list[node].ants >= 0)
		{
			if (node != g->start && !g->map.list[parents[node]].mem_link
				&& parents[g->map.list[node].ants] == (uint)-1)
			{
				g->map.list[node].mem_link = 1;
				g->map.list[g->map.list[node].ants].mem_link = 1;
				parents[g->map.list[node].ants] = node;
				que_push(q, g->map.list[node].ants);
				continue ;
			}
			else if (!superpo)
				continue ;
		}
		tmp = -1;
		while (++tmp < g->map.list[node].nb_link)
		{
			tmp_lnk = g->map.list[node].links[tmp];
			if (!(tmp_lnk & LNK_VISITED) && parents[tmp_lnk] == (uint)-1)
			{
				parents[tmp_lnk] = node;
				if (tmp_lnk == g->end)
					return (1);
				if (g->map.list[node].mem_link && g->map.list[node].ants >= 0)
					g->map.list[tmp_lnk].mem_link = 1;
				que_push(q, tmp_lnk);
			}
		}
	}
	return (0);
}

void			edmonds_karp(t_graph *g, t_vector *path, int mx_pths,
	int super_po)
{
	t_queue		*q;
	uint		*parents;
	int			nb_paths;
	uint		i;

	q = que_new(g->map.used);
	if (!(parents = malloc(g->map.used * sizeof(uint))))
		exit_clean(g, 1);
	nb_paths = 0;
	clean_graph_everything(g);
	while (++nb_paths < mx_pths)
	{
		ft_mem32set(parents, -1, g->map.used);
		que_flush(q);
		clean_graph_memlnk(g);
		if (!bfs(g, parents, q, super_po))
			break ;
		write_path(g, parents);
	}
	que_destroy(q);
	free(parents);
	i = -1;
	while (++i < g->map.used)
		g->map.list[i].ants = 0;
	compute_paths(g, path, nb_paths, super_po);
}

void			find_paths(t_graph *graph, t_str *str)
{
	t_vector	paths[2];
	int			which_one_do_we_use;

	if (!vector_init(&paths[0], 10) || !vector_init(&paths[1], 10))
		exit_clean(graph, 1);
	edmonds_karp(graph, &paths[0], 99999, 0);
	clean_graph_everything(graph);
	edmonds_karp(graph, &paths[1], 99999, 1);
	clean_graph_everything(graph);
	which_one_do_we_use = (paths[0].arr->len + paths[0].arr->ants_to_lanch)
		< (paths[1].arr->len + paths[1].arr->ants_to_lanch) ? 0 : 1;
	destroy_paths(&paths[!which_one_do_we_use]);
	if (paths[which_one_do_we_use].len == 0)
		exit_clean(graph, 1);
	display_t_str(str);
	send_ants(graph, &paths[which_one_do_we_use]);
}
