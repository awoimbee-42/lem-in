/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/03 16:33:56 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			sort_paths(t_vector *p)
{
	t_path		buff;
	uint32_t	i;

	i = -1;
	while (++i < p->len - 1)
	{
		if (p->arr[i].len > p->arr[i + 1].len)
		{
			buff = p->arr[i];
			p->arr[i] = p->arr[i + 1];
			p->arr[i + 1] = buff;
			i = -1;
		}
	}
}

static void		cpy_path2(t_graph *g, uint32_t node, t_path *p)
{
	uint32_t	i;

	p->len = 0;
	p->dirs = malloc(sizeof(*p->dirs) * g->map.used);
	while (node != g->end)
	{
		ft_printf("%s --> ", g->map.list[node].name);
		p->dirs[p->len++] = node;
		i = -1;
		while (++i < g->map.list[node].nb_link && !(g->map.list[node].links[i] & LNK_VISITED))
			;
		if (i == g->map.list[node].nb_link)
			ft_printf(" Fuck me "); // /!\ l
		node = g->map.list[node].links[i] & ~LNK_VISITED;
	}
	p->dirs[p->len++] = node;
	ft_printf("\n");
}

void			graph_to_paths(t_graph *g, t_vector *paths)
{
	uint32_t	node;
	t_path		p;
	uint32_t	i;

	node = g->start;
	i = -1;
	while (++i < g->map.list[g->start].nb_link)
	{
		if (g->map.list[g->start].links[i] & LNK_VISITED)
		{
			cpy_path2(g, g->map.list[g->start].links[i] & ~LNK_VISITED, &p);
			vector_push(paths, p);
		}
	}
}

/*
**	This is the function called at the end of BFS, it cpoies the path but also
**		marks nodes as visited
*/

static int		write_path(t_graph *g, uint32_t *parents, t_vector *path_vec)
{
	uint32_t	node;
	t_path		p;

	ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[g->end].name);
	// p.len = 0;
	// p.dirs = malloc(sizeof(*p.dirs) * g->map.used);
	node = g->end;
	while (node != g->start)
	{
		{
			uint32_t *lnkptr;

			lnkptr = g->map.list[node].links;
			while ((*lnkptr & ~LNK_VISITED) != parents[node])
				++lnkptr;
			if (*lnkptr & LNK_VISITED)
				*lnkptr &= ~LNK_VISITED;
			else
			{
				lnkptr = g->map.list[parents[node]].links;
				while (*lnkptr != node)
					++lnkptr;
				*lnkptr |= LNK_VISITED;
			}
		}
		// if (node != g->end)
			// g->map.list[node].ants = 1;     //mark as visited
		ft_printf("{blu}%s <-- {eoc}", g->map.list[node].name);
		// p.dirs[p.len++] = node;         // add to path
		node = parents[node];
	}
	// if (!vector_push(path_vec, p))
		// exit_lem_in("Memory allcation error in cpy_path");
	ft_printf("{blu}%s{eoc}\n\n\n", g->map.list[g->start].name);
	return (1);
}

static int		bfs(t_graph *g, uint32_t *parents, t_queue *q)
{
	uint32_t	node;
	uint32_t	tmp;
	uint32_t	tmp_lnk;

	if (!que_push(q, g->start))
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
			if (!(tmp_lnk & LNK_VISITED) && parents[tmp_lnk] == (uint32_t)-1)
			{
				if (g->map.list[tmp_lnk].ants != 0)
					; // overlap
				parents[tmp_lnk] = node;
				if (tmp_lnk == g->end)
					return (1);
				que_push(q, tmp_lnk);
			}
		}
	}
	return (0);
}

void		edmonds_karp(t_graph *g, t_vector *paths)
{
	t_queue		*q;
	uint32_t	*parents;
	uint32_t	i;

	q = que_new(g->map.used);
	parents = ft_memalloc(g->map.used * sizeof(uint32_t));
	i = -1;
	while (++i < g->ants)
	{
		ft_bzero(parents, g->map.used * sizeof(uint32_t));
		que_flush(q);
		if (!bfs(g, parents, q))
			break ;
		write_path(g, parents, paths);
	}
	que_destroy(q);
	free(parents);
	graph_to_paths(g, paths);
	sort_paths(paths);
}

void		find_paths(t_graph *graph, t_str *str)
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
	if (paths.len == 0)
		exit_clean(graph, 1);
	display_t_str(str);
	send_ants(graph, &paths);
}
