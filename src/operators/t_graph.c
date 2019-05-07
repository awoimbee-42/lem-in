/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_graph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:55:10 by allespag          #+#    #+#             */
/*   Updated: 2019/05/08 00:57:45 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph			*init_graph(void)
{
	t_graph		*new;

	if (!(new = (t_graph *)malloc(sizeof(t_graph))))
		exit_lem_in("Error: graph malloc failed in init_graph\n");
	new->ants = 0;
	new->start = UINT32_NOT_SET;
	new->end = UINT32_NOT_SET;
	new->map.size = DEFMALLOCMAP;
	new->print = 0;
	if (!(new->map.list = ft_memalloc(sizeof(t_room) * new->map.size)))
		exit_lem_in("Error: map malloc failed in init_graph\n");
	new->map.used = 0;
	return (new);
}

void			free_t_graph(t_graph *g)
{
	uint32_t	i;

	if (g)
	{
		i = -1;
		while (++i < g->map.used)
		{
			ft_memdel((void**)&g->map.list[i].name);
			ft_memdel((void**)&g->map.list[i].links);
		}
		ft_memdel((void**)&g->map.list);
		ft_memdel((void**)&g);
	}
}

void			display_graph(t_graph *g)
{
	ft_putstr("Ants: ");
	ft_putnbr(g->ants);
	ft_putstr("\nStart: ");
	display_room(&g->map.list[g->start], 0);
	ft_putstr("End: ");
	display_room(&g->map.list[g->end], 0);
}
