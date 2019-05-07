/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/07 17:50:03 by awoimbee         ###   ########.fr       */
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
	parents[g->start] = -2;
	while (!que_isempty(q))
	{
		node = que_pop(q);
		tmp = -1;
		if (g->map.list[node].ants >= 0)
		{
			if (node != g->start && !g->map.list[parents[node]].mem_link)
			{
				ft_printf("{ylw}screw your optics, \"%s\" (node: %s){eoc}\n", g->map.list[g->map.list[node].ants].name, g->map.list[node].name);
				g->map.list[node].mem_link = 1;
				parents[g->map.list[node].ants] = node;
				que_push(q, g->map.list[node].ants);
				continue ;
			}
			else ft_printf("PUTE %u\n", g->map.list[parents[node]].mem_link);
			// g->map.list[node].ants = -1;
		}
		while (++tmp < g->map.list[node].nb_link)
		{
			tmp_lnk = g->map.list[node].links[tmp];

			if (!(tmp_lnk & LNK_VISITED) && parents[tmp_lnk] == (uint32_t)-1)
				// && (g->map.list[tmp_lnks].ants < 0 || g->map.list[parents[node]].mem_link))
					// || (int)(tmp_lnk & ~LNK_VISITED) == g->map.list[node].ants ) )
			{
				// ft_printf("{grn}yass \"%s\" (node: %s){eoc}\n", g->map.list[tmp_lnk & ~LNK_VISITED].name, g->map.list[node].name);
				parents[tmp_lnk & ~LNK_VISITED] = node;
				if ((tmp_lnk & ~LNK_VISITED) == g->end)
					return (1);
				if (g->map.list[node].mem_link && g->map.list[node].ants >= 0)
					g->map.list[tmp_lnk & ~LNK_VISITED].mem_link = 1;
				que_push(q, tmp_lnk & ~LNK_VISITED);
			}
			else
			{
				// ft_printf("{red}fuck you \"%s\" (node: %s) tmp_lnk: %u parents[tmp_lnk]: %u{eoc}\n", g->map.list[tmp_lnk & ~LNK_VISITED].name, g->map.list[node].name, tmp_lnk, parents[tmp_lnk & ~LNK_VISITED]);
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
	if (!(parents = malloc(g->map.used * sizeof(uint32_t))))
		exit_clean(g, 1);
	nb_paths = 0;
	clean_graph_everything(g);
	while (++nb_paths < max_paths)
	{
		ft_mem32set(parents, -1, g->map.used);
		que_flush(q);
		clean_graph_memlnk(g);
		if (!bfs(g, parents, q))
			break ;
		ft_printf("############  write path  ############\n");
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
		exit_clean(graph, 1);
	edmonds_karp(graph, &paths, 99999);
	if (paths.len == 0)
		exit_clean(graph, 1);
	display_t_str(str);
	clean_graph_everything(graph);
	send_ants(graph, &paths);
}
