/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_room.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:23:09 by allespag          #+#    #+#             */
/*   Updated: 2019/04/08 17:10:44 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*new_room(char *name, int ants, int x, int y)
{
	t_room		*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		exit_lem_in("Error: malloc failed in new_room\n");
	new->name = name;
	new->ants = ants;
	new->coords.x = x; // fdp de tes morts tu check pas les coordonnees
	new->coords.y = y;
	new->linked.used = 0;
	new->linked.size = 10;
	if (!(new->linked.list = malloc(DEF_MALLOC_MAP * sizeof(*new->linked.list))))
		exit_lem_in("couldnt malloc links in new_room");
	// new->linked = new_t_map(10);
	return (new);
}

void			free_room(t_room *room)
{
	if (room)
	{
		ft_memdel((void*)&room->name);
		ft_memdel((void*)&room->linked.list);
		//ft_memdel((void*)&room); //unused ?
	}
}

int				cmp_room(t_room *a, t_room *b)
{
	if (!ft_strcmp(a->name, b->name)
		|| (a->coords.x == b->coords.x && a->coords.y == b->coords.y))
		return (0);
	return (1);
}

void			display_room(t_room *room, int map)
{
	if (!room)
		ft_putendl("romm est null yes");
	ft_putstr("Room: ");
	ft_putendl(room->name);
	ft_putstr("Ants: ");
	ft_putnbr(room->ants);
	ft_printf("\nCoord: %d %d\n", room->coords.x, room->coords.y);
	if (map)
	{
		ft_putendl("linked: ");
		display_map(&room->linked);
	}
}
