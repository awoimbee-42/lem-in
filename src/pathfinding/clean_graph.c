/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:54:15 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/11 14:46:15 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		clean_graph_ants_mem(t_graph *g)
{
	uint	i;

	i = -1;
	while (++i < g->map.used)
	{
		g->map.list[i].ants = -1;
		g->map.list[i].mem_link = 0;
	}
}

void		clean_graph_links(t_graph *g)
{
	uint	i[2];

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

void		clean_graph_everything(t_graph *g)
{
	uint	i[2];

	i[0] = -1;
	while (++i[0] < g->map.size)
	{
		g->map.list[i[0]].ants = -1;
		g->map.list[i[0]].mem_link = 0;
		i[1] = -1;
		while (++i[1] < g->map.list[i[0]].nb_link)
		{
			g->map.list[i[0]].links[i[1]] &= ~LNK_VISITED;
		}
	}
}

void		clean_graph_memlnk(t_graph *g)
{
	uint	i;

	i = -1;
	while (++i < g->map.used)
		g->map.list[i].mem_link = 0;
}
