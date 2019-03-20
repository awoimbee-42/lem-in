/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:55:10 by allespag          #+#    #+#             */
/*   Updated: 2019/03/20 16:27:45 by allespag         ###   ########.fr       */
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
	new->map = new_t_map(10);
	return (new);
}

void			display_map(t_map *map)
{
	size_t		i;

	i = 0;
	ft_putstr("---------------------\n");
	while (i < map->used)
	{
		display_room(&map->list[i], 0);
		i++;
		ft_putchar('\n');
	}
	ft_putstr("---------------------\n");
}

void			display_room(t_room *room, int map)
{
	ft_putstr("Room: ");
	ft_putendl(room->name);
	ft_putstr("Ants: ");
	ft_putnbr(room->ants);
	ft_printf("\nCoord: %d %d\n", room->x, room->y);
	if (map)
	{
		ft_putendl("linked: ");
		display_map(room->linked);
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
