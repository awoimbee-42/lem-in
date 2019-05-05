/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_to_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:03:32 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/05 20:06:23 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		sort_paths(t_vector *p)
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
	p->dirs = malloc(sizeof(*p->dirs) * g->map.used); // /!\ EKLFEF
	while (node != g->end)
	{
		ft_printf("%s --> ", g->map.list[node].name);
		g->map.list[node].ants = 1;
		p->dirs[p->len++] = node;
		i = -1;
		while (++i < g->map.list[node].nb_link
			&& !(g->map.list[node].links[i] & LNK_VISITED))
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
	sort_paths(paths);
}
