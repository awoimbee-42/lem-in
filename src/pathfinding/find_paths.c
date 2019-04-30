/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/30 17:32:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//use ants to signal if already searched
//cut useless
//

#define MAX_PATHS 256

typedef struct		s_path
{
	uint32_t	len;
	int			overlaps[2]; // <- 4 overlaps is already quite a bit
	uint32_t	*dirs;
}					t_path;

static int		cpy_path(t_graph *g, uint32_t *parents, t_path *path)
{
	uint32_t	node;

				ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[g->end].name);
	path->len = 0;
	node = parents[g->end];
	while (node != g->start)
	{
		g->map.list[node].ants = 1;      //mark as visited
				ft_printf("{blu}%s <-- {eoc}", g->map.list[node].name);
		path->dirs[path->len++] = node; // add to path
		node = parents[node];           // go to parent
	}
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
			if (parents[tmp_lnk] == -1 && g->map.list[tmp_lnk].ants == 0)
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

void		edmonds_karp(t_graph *g, t_path *paths)
{
	t_queue		*q;
	uint32_t	*parents;

	q = que_new(g->map.used);
	parents = ft_memalloc(g->map.used * sizeof(uint32_t));
	int i = -1;
	while (++i < MAX_PATHS)
	{
		ft_bzero(parents, g->map.used * sizeof(uint32_t));
		que_flush(q);
		paths[i].dirs = malloc(g->map.used * sizeof(*paths[i].dirs));
		if (!bfs(g, parents, q))
			break ;
		cpy_path(g, parents, &paths[i]);
	}
}

void		find_paths(t_graph *graph)
{
	t_path		*paths;

	paths = (t_path*)ft_memalloc(sizeof(*paths) * 256); // TO PROTEC
	edmonds_karp(graph, paths);
	ft_printf("{PNK}END OF BFS, PATHS:{eoc}\n");
	for (t_path *p = &paths[1]; p->len != 0; ++p)
	{
		for (uint32_t xyz = 0; xyz < p->len; ++xyz)
			ft_printf("-->%s\n", graph->map.list[p->dirs[xyz]].name);
		ft_printf("\n\n");
	}


}
