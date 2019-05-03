/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/03 19:11:50 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				calc_ants_to_launch(t_graph *g, t_vector *vec)
{
	uint32_t	i;
	uint32_t	paths_len_sum;
	int			ants_launched;
	int			delta_ants;

	ants_launched = 0;
	paths_len_sum = 0;
	i = -1;
	while (++i < vec->len)
		paths_len_sum += vec->arr[i].len;
	i = -1;
	while (++i < vec->len)
	{
		// ft_printf("vec->arr[i].ants_to_lanch = (%u - ((%u - 1) * %u - (%u - %u))) / %u;\n", g->ants, vec->len - 1, vec->arr[i].len, paths_len_sum, vec->arr[i].len, vec->len);
		vec->arr[i].ants_to_lanch = ((int)g->ants - (((int)vec->len - 1) * (int)vec->arr[i].len - ((int)paths_len_sum - (int)vec->arr[i].len))) / (int)vec->len;
		ants_launched += vec->arr[i].ants_to_lanch;
		if (vec->arr[i].ants_to_lanch < 0)
			return (vec->len - i); // too many paths !!!
		// ft_printf("{PNK}paths %u, len %u, ants to launch %d{eoc}\n", i, vec->arr[i].len, vec->arr[i].ants_to_lanch);
	}
	delta_ants = (int)g->ants - ants_launched;
	ants_launched = delta_ants > 0 ? 1 : -1;
	i = -1;
	while (++i < vec->len && delta_ants != 0)
	{
		vec->arr[i].ants_to_lanch += ants_launched;
		delta_ants -= ants_launched;
	}
	return (0);
}

void			sort_paths(t_vector *p)
{
	t_path		buff;
	uint32_t	i;

	if (p->len == 0)
		return ;
	i = -1;
	while (++i < p->len - 1)
	{
		if (p->arr[i].len > p->arr[i + 1].len)
		{
			buff = p->arr[i];
			p->arr[i] = p->arr[i + 1];
			p->arr[i + 1] = buff;
			i = i < 2 ? -1 : i - 2;
		}
	}
}

static int		cpy_path2(t_graph *g, uint32_t node, t_path *p)
{
	uint32_t	i;

	p->len = 0;
	p->dirs = malloc(sizeof(*p->dirs) * g->map.used);
	while (node != g->end)
	{
		ft_printf("%s --> ", g->map.list[node].name);
		g->map.list[node].ants = 1;
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
	return (1);
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
			if (cpy_path2(g, g->map.list[g->start].links[i] & ~LNK_VISITED, &p))
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
	uint32_t	*lnkptr;

	ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[g->end].name);
	node = g->end;
	while (node != g->start)
	{
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
		ft_printf("{blu}%s <-- {eoc}", g->map.list[node].name);
		node = parents[node];
	}
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

void		clean_links(t_graph *g)
{
	uint32_t	i[2];

	i[0] = -1;
	while (++i[0] < g->map.size)
	{
		i[1] = -1;
		while (++i[1] < g->map.list[i[0]].nb_link)
		{
			g->map.list[i[0]].links[i[1]] &= ~LNK_VISITED;
		}
	}
}

void		remove_overlapping_paths(t_graph *g, t_vector *vec)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < g->map.used)
		if (i != g->start)
			g->map.list[i].ants = 0;
	i = -1;
	while (++i < vec->len)
	{
		j = -1;
		while (vec->arr[i].dirs[++j] != g->end)
		{
			if (g->map.list[vec->arr[i].dirs[j]].ants)
			{
				ft_printf("\n\nOVERLAP\n\n");
				vector_del_at(vec, i);
				--i;
				break ;
			}
			g->map.list[vec->arr[i].dirs[j]].ants = 1;
		}
	}
}


void		compute_paths(t_graph *g, t_vector *vec, int max_p, int nb_p)
{
	uint32_t	nb_paths_over;
	uint32_t	i;


	graph_to_paths(g, vec);
	sort_paths(vec);
	remove_overlapping_paths(g, vec);
	if ((nb_paths_over = calc_ants_to_launch(g, vec)))
	{
		clean_links(g);
		vec->len = 0;
		edmonds_karp(g, vec, nb_p - nb_paths_over);
	}
}

void		edmonds_karp(t_graph *g, t_vector *paths, uint32_t max_paths)
{
	t_queue		*q;
	uint32_t	*parents;
	uint32_t	nb_paths;

	q = que_new(g->map.used);
	parents = ft_memalloc(g->map.used * sizeof(uint32_t));
	nb_paths = -1;
	while (++nb_paths < max_paths)
	{
		ft_bzero(parents, g->map.used * sizeof(uint32_t));
		que_flush(q);
		if (!bfs(g, parents, q))
			break ;
		write_path(g, parents, paths);
	}
	que_destroy(q);
	free(parents);
	compute_paths(g, paths, max_paths, nb_paths);
}

void		find_paths(t_graph *graph, t_str *str)
{
	t_vector	paths;

	if (!vector_init(&paths, 10))
		exit_lem_in("Cannot allocate memory for paths vector");
	edmonds_karp(graph, &paths, 99999);
	{
		for (size_t i = 0; i < paths.len; ++i)
		{
			for (uint32_t xyz = 0; xyz < paths.arr[i].len; ++xyz)
				ft_printf("-->%s\n", graph->map.list[paths.arr[i].dirs[xyz]].name);
			ft_printf("\n\n");
		}
	}
	if (paths.len == 0)
		exit_clean(graph, 1);
	display_t_str(str);
	send_ants(graph, &paths);
}
