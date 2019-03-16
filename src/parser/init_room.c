/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:58:15 by allespag          #+#    #+#             */
/*   Updated: 2019/03/16 18:40:26 by allespag         ###   ########.fr       */
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
	new->x = x;
	new->y = y;
	new->linked = NULL;
	return (new);
}

void			room_free(t_room *room)
{
	if (room)
	{
		if (room->name)
			free(room->name);
		//creer free_linked
		//if (linked)
		//	free_linked(room->linked);
		free(room);
	}
}
