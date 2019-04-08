/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_graph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:55:10 by allespag          #+#    #+#             */
/*   Updated: 2019/04/08 16:57:07 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph			*init_graph(void)
{
	t_graph		*new;

	if (!(new = (t_graph *)malloc(sizeof(t_graph))))
		exit_lem_in("Error: malloc failed in init_graph\n");
	new->ants = 0;
	new->start = NULL;
	new->end = NULL;
	new->map = new_t_map();
	return (new);
}

//il manque des trucs a free
void			free_t_graph(t_graph *g)
{
	if (g)
	{
		if (g->map)
			free_t_map(g->map, 1);
		free(g);
	}
}

void			display_graph(t_graph *g)
{
	ft_putstr("Ants: ");
	ft_putnbr(g->ants);
	ft_putstr("\nStart: ");
	display_room(g->start, 0);
	ft_putstr("End: ");
	display_room(g->end, 0);
	ft_putendl("Map: ");
	display_map(g->map);
}
