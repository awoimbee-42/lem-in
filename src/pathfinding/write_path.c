/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:38:04 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/11 14:49:19 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	This is the function called at the end of BFS, it writes down the final path
**		into the graph, marking links as visited and writing in 'ants' the
**		parent of each node.
**	One problem we have is ithat wwhen going upstream (deactivating paths),
**		which node should we strip of it's parents ?
**	Right now we are being too nazi:
**		on the youtube map we go from 14 to 19 steps.
*/

/*
**	if inverse link exists, i remove it
**	else i write the path as normal
*/

static void	write_flow(t_graph *g, uint *parents)
{
	uint	node;
	uint	*lnkptr;

	node = g->end;
	while (node != g->start)
	{
		g->map.list[node].ants = -1;
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
		node = parents[node];
	}
}

static void	write_parents(t_graph *g)
{
	uint	i;
	uint	j;
	uint	node;
	uint	parent;

	i = -1;
	while (++i < g->map.list[g->start].nb_link)
	{
		parent = g->start;
		if (g->map.list[g->start].links[i] & LNK_VISITED)
		{
			node = g->map.list[g->start].links[i] & ~LNK_VISITED;
			while (node != g->end)
			{
				g->map.list[node].ants = parent;
				j = -1;
				while (++j < g->map.list[node].nb_link
					&& !(g->map.list[node].links[j] & LNK_VISITED))
					;
				parent = node;
				node = g->map.list[node].links[j] & ~LNK_VISITED;
			}
		}
	}
}

void		write_path(t_graph *g, uint *parents)
{
	write_flow(g, parents);
	write_parents(g);
}
