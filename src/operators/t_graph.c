/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_graph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:55:10 by allespag          #+#    #+#             */
/*   Updated: 2019/04/10 21:01:00 by awoimbee         ###   ########.fr       */
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
	if (!(new->map.list = malloc(sizeof(t_room) * new->map.size)))
		exit_lem_in("Error: map malloc failed in init_graph\n");
	new->map.used = 0;
	return (new);
}

void			free_t_graph(t_graph *g)
{
	if (g)
	{
		free_t_map(&g->map, 1);
		free(g);
	}
}

void			display_graph(t_graph *g, int print_links)
{
	ft_putstr("Ants: ");
	ft_putnbr(g->ants);
	ft_putstr("\nStart: ");
	display_room(&g->map.list[g->start], 0);
	ft_putstr("End: ");
	display_room(&g->map.list[g->end], 0);
	ft_putendl("Map: ");
	display_map(&g->map, 0);
}
