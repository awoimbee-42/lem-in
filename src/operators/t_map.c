/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:01:35 by allespag          #+#    #+#             */
/*   Updated: 2019/04/09 21:00:37 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_map			*new_t_map()
{
	t_map		*new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		exit_lem_in("Error: malloc (1st) failed in new_t_map");
	if (!(new->list = (t_room *)malloc(sizeof(t_room) * DEF_MALLOC_MAP)))
		exit_lem_in("Error: malloc (2nd) failed in new_t_map");
	new->size = DEF_MALLOC_MAP;
	new->used = 0;
	return (new);
}

void			free_t_map(t_map *map, int free_sub)
{
	size_t		i;

	i = 0;
	if (map)
	{
		if (map->list)
		{
			while (free_sub && i < map->used)
			{
				free_room(&map->list[i]);
				i++;
			}
			free(map->list);
			map->list = NULL;
		}
	}
}

void			realloc_t_map(t_map *map)
{
	t_room		*new_list;

	if (!(new_list = malloc(sizeof(*map->list) * map->size * REALLOC_COEFF)))
		exit_lem_in("Error: malloc in realloc_t_map\n");
	ft_mempcpy(new_list, map->list, map->used * sizeof(*map->list));
	free(map->list);
	map->list = new_list;
	map->size *= REALLOC_COEFF;
}

void			add_t_map(t_map *map, t_room *add)
{
	if (map->used == map->size)
		realloc_t_map(map);
	map->list[map->used++] = *add;
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

// unused maybe ?
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
