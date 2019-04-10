/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_room.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:23:09 by allespag          #+#    #+#             */
/*   Updated: 2019/04/10 20:35:52 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void			reset_room(t_room *tmp_room)
{
	tmp_room->ants = 0;
	tmp_room->name = NULL;
	tmp_room->nb_link = 0;
	tmp_room->mem_link = 0;
	tmp_room->links = NULL;
}

// t_room			*new_room(char *name, int ants, int x, int y)
// {
// 	t_room		*new;

// 	if (!(new = (t_room *)malloc(sizeof(t_room))))
// 		exit_lem_in("Error: malloc failed in new_room\n");
// 	new->name = name;
// 	new->ants = ants;
// 	new->coords.x = x;
// 	new->coords.y = y;
// 	new->nb_link = 0;
// 	new->mem_link = 10;
// 	if (!(new->links = malloc(DEFMALLOCMAP * sizeof(*new->links))))
// 		exit_lem_in("couldnt malloc links in new_room\n");
// 	return (new);
// }

void			free_room(t_room *room)
{
	if (room)
	{
		ft_memdel((void*)&room->name);
		ft_memdel((void*)&room->links);
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

void			display_room(const t_room *room, const t_graph *maybe_graph)
{
	if (!room)
		ft_putendl("romm est null yes");
	ft_putstr("Room: ");
	ft_putendl(room->name);
	ft_putstr("Ants: ");
	ft_putnbr(room->ants);
	ft_printf("\nCoord: %d %d\n", room->coords.x, room->coords.y);
	if (maybe_graph)
	{
		ft_putendl("linked: ");
		display_links(room, maybe_graph);
	}
}
