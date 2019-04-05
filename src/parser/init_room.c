/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:23:09 by allespag          #+#    #+#             */
/*   Updated: 2019/04/05 21:56:36 by awoimbee         ###   ########.fr       */
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
	new->coords.x = x;
	new->coords.y = y;
	// new->linked.used = 0;
	// if (!(new->linked.list = malloc(10 * sizeof(*new->linked.list))))
	new->linked = new_t_map(10);
	return (new);
}

void			room_free(t_room *room)
{
	if (room)
	{
		if (room->name)
		{
			free(room->name);
			room->name = NULL;
		}
		if (room->linked)
			free_t_map(room->linked, 0);
	}
}

// NORME ICI POUR LE RETURN 0 JE SAIS PAS
int				cmp_room(t_room *a, t_room *b)
{
	if (!ft_strcmp(a->name, b->name)
			|| (a->coords.x == b->coords.x && a->coords.y == b->coords.y))
		return (0);
	return (1);
}
