/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/13 02:59:29 by awoimbee         ###   ########.fr       */
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


static int		cpy_path(t_graph *g, uint32_t *parents, t_path *path, int *id)
{
	uint32_t	node;

				ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[g->end].name);
	path->len = 0;
	node = g->end;
	while (node != g->start)
	{
				ft_printf("{blu}%s <-- {eoc}", g->map.list[node].name);
		path->dirs[path->len++] = node;
		node = parents[node];
	}
				ft_printf("{blu}%s{eoc}\n\n\n", g->map.list[g->start].name);
	++*id;
	return (1);
}

//this function is shitty, needs work
static void	handle_overlap(int prev_p_id, t_path *path, uint32_t *prev_par)
{
	int			i;

	i = 0;
	while (path->overlaps[i] != 0)
	{
		if (i == 3 || path->overlaps[i] == prev_p_id) // only 1 overlap is allowed
		{
			ft_printf(" i == 3 ");
			return ;
		}
		++i;
	}
	path->overlaps[i] = prev_p_id;
	*prev_par = UINT32_NOT_SET;
}

// this piece of shit only finds 1 path ffs
static void		bfs(t_graph *g, int id, t_path *paths)
{
	t_queue		*q;
	uint32_t	node;
	uint32_t	tmp;
	uint32_t	*parents;
	uint32_t	tmp_lnk;

	if (!(q = que_new(g->map.used)) || !que_push(q, g->start))
		exit_lem_in("Could not create queue, bfs cannot continue");
	if (!(parents = ft_memalloc(g->map.used * sizeof(uint32_t))))
		exit_lem_in("Could not allocate memory in bfs() for parents");
	ft_mem32set(parents, UINT32_NOT_SET, g->map.used);

	while (!que_isempty(q))
	{
		if ((node = que_pop(q)) == (t_queued)-1)
			exit_lem_in("Queue shall not be empty, memory corruption ?");
		if (node == g->end && cpy_path(g, parents, &paths[id], &id) && que_push(q, g->start))
			continue ;
		g->map.list[node].ants = id; // need to check if not visited by other instance
						ft_printf("{inv}%s<rst> links to :\n", g->map.list[node].name);
		tmp = -1;
		while (++tmp < g->map.list[node].nb_link)
		{
			tmp_lnk = g->map.list[node].links[tmp];
			ft_printf("\t-> %s\n", g->map.list[tmp_lnk].name);
			if (parents[tmp_lnk] != UINT32_NOT_SET && g->map.list[parents[tmp_lnk]].ants != id)
			{
				ft_printf("OUGABOUGA %s parents == %u", g->map.list[tmp_lnk].name, parents[tmp_lnk]);
				handle_overlap(g->map.list[tmp_lnk].ants, &paths[id], &parents[tmp_lnk]);
				ft_printf(" updated to %u\n", parents[tmp_lnk]);
			}

			if (parents[tmp_lnk] == UINT32_NOT_SET)
			{
				parents[tmp_lnk] = node;
				if (!que_push(q, tmp_lnk))
					exit_lem_in("Could not update queue, memory corruption ?");
			}

		}
	}
	que_destroy(q);
}

void		find_paths(t_graph *graph)
{
	t_path		*paths;

	paths = &((t_path*)ft_memalloc(sizeof(*paths) * 256))[-1];
	int i = 0;
	while (++i <= 256)
		paths[i].dirs = malloc(graph->map.used * sizeof(*paths[i].dirs));
	bfs(graph, 1, paths);
	ft_printf("{PNK}END OF BFS, PATHS:{eoc}\n");
	for (t_path *p = &paths[1]; p->len != 0; ++p)
	{
		for (uint32_t xyz = 0; xyz < p->len; ++xyz)
			ft_printf("-->%s\n", graph->map.list[p->dirs[xyz]].name);
		ft_printf("\n\n");
	}


}
