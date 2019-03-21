/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 22:40:16 by allespag          #+#    #+#             */
/*   Updated: 2019/03/20 17:46:53 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_map			*new_t_map(size_t size)
{
	t_map		*new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		exit_lem_in("Error: malloc (1st) failed in new_t_map");
	if (!(new->list = (t_room *)malloc(sizeof(t_room) * size)))
		exit_lem_in("Error: malloc (2nd) failed in new_t_map");
	new->size = size;
	new->used = 0;
	return (new);
}

void			free_t_map(t_map *map)
{
	size_t		i;

	i = 0;
	if (map)
	{
		if (map->list)
		{
		//	while (i < map->used)
		//	{
		//		room_free(&map->list[i]);
		//		i++;
		//	}
			free(map->list);
		}
		free(map);
	}
}

t_map			*realloc_t_map(t_map *map)
{
	size_t		i;
	t_map		*new;

	i = 0;
	new = new_t_map(map->size * 2);
	new->used = map->used;
	while (i < map->size)
	{
		new->list[i] = map->list[i];
		i++;
	}
	return (new);
}

t_map			*add_t_map(t_map *map, t_room *add)
{
	t_map		*tmp;

	if (map->used >= map->size)
	{
		tmp = realloc_t_map(map);
		//free un truc qu'il fallait pas ici
		free_t_map(map);
		tmp->list[tmp->used] = *add;
		tmp->used++;
		return (tmp);
	}
	map->list[map->used] = *add;
	map->used++;
	return (map);
}

int					is_room_here(t_map *map, t_room *room)
{
	size_t			i;

	i = 0;
	while (i < map->used)
	{
		if (!cmp_room(&map->list[i], room))
			return (1);
		i++;
	}
	return (0);
}
