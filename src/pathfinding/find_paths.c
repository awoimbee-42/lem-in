/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/01 19:06:33 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define MAX_PATHS 256

// path is reversed !!

static int		cpy_path(t_graph *g, uint32_t *parents, t_vector *path_vec)
{
	uint32_t	node;
	t_path		p;

				ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[g->end].name);
	p.len = 0;
	p.dirs = malloc(sizeof(*p.dirs) * g->map.used);
	node = g->end;
	// p.dirs[p.len++] = g->end;
	while (node != g->start)
	{
		if (node != g->end)
			g->map.list[node].ants = 1;     //mark as visited
				ft_printf("{blu}%s <-- {eoc}", g->map.list[node].name);
		p.dirs[p.len++] = node;         // add to path
		node = parents[node];
	}
	if (!vector_push(path_vec, p))
		exit_lem_in("Memory allcation error in cpy_path");
				ft_printf("{blu}%s{eoc}\n\n\n", g->map.list[g->start].name);
	return (1);
}

static int		bfs(t_graph *g, uint32_t *parents, t_queue *q)
{
	uint32_t	node;
	uint32_t	tmp;
	uint32_t	tmp_lnk;

	if (!(q = que_new(g->map.used)) || !que_push(q, g->start))
		exit_lem_in("Could not create queue, bfs cannot continue");
	ft_mem32set(parents, -1, g->map.used);
	parents[g->start] = -2;
	while (!que_isempty(q))
	{
		node = que_pop(q);
		tmp = -1;
		while (++tmp < g->map.list[node].nb_link)
		{
			tmp_lnk = g->map.list[node].links[tmp];
			if (parents[tmp_lnk] == (uint32_t)-1 && g->map.list[tmp_lnk].ants == 0)
			{
				parents[tmp_lnk] = node;
				if (tmp_lnk == g->end)
					return (1);
				que_push(q, tmp_lnk);
			}
		}
	}
	que_destroy(q);
	return (0);
}

void		edmonds_karp(t_graph *g, t_vector *paths)
{
	t_queue		*q;
	uint32_t	*parents;

	q = que_new(g->map.used);
	parents = ft_memalloc(g->map.used * sizeof(uint32_t));
	while (1)
	{
		ft_bzero(parents, g->map.used * sizeof(uint32_t));
		que_flush(q);
		if (!bfs(g, parents, q))
			break ;
		cpy_path(g, parents, paths);
	}
}

void		find_paths(t_graph *graph)
{
	t_vector	paths;

	if (!vector_init(&paths, 10))
		exit_lem_in("Cannot allocate memory for paths vector");
	edmonds_karp(graph, &paths);
	ft_printf("{PNK}END OF BFS, PATHS:{eoc}\n");
	for (size_t i = 0; i < paths.len; ++i)
	{
		for (uint32_t xyz = 0; xyz < paths.arr[i].len; ++xyz)
			ft_printf("-->%s\n", graph->map.list[paths.arr[i].dirs[xyz]].name);
		ft_printf("\n\n");
	}
}
