/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:05:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/01 18:51:45 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		weird_reset_rooms(t_map *m)
{
	t_room		*ptr;
	t_room		*map_end;

	ptr = m->list;
	map_end = &ptr[m->used];
	while (ptr != map_end)
	{
		ptr->coords.x = 0;
		ptr->coords.y = 0;
		ptr->ants = 0;
		++ptr;
	}
}

// ants_nb = ant_id
// coords.x = ant_path_id
// coords.y = ant_path_step

void		move_ants(t_graph *g, t_vector *paths)
{
	int			curr_p;
	uint32_t	*p_ptr;
	uint32_t	*p_start;

	curr_p = -1;
	while (++curr_p < paths->len)
	{
		p_ptr = paths->arr[curr_p].dirs;
		p_start = paths->arr[curr_p].dirs[paths->arr[curr_p].len];
		while (++p_ptr < p_start)
		{
			if (g->map.list[*p_ptr].ants != 0) // if there is an ant
			{
				if (*(p_ptr - 1) == g->end) // path go to sink
				{
					g->map.list[*(p_ptr - 1)].ants += 1;
				}
				else
				{
					g->map.list[*(p_ptr - 1)].ants = g->map.list[*p_ptr].ants;
					// g->map.list[*(p_ptr - 1)].coords.x = g->map.list[*p_ptr].coords.x; // no overlap so unused
					// g->map.list[*(p_ptr - 1)].coords.y = g->map.list[*p_ptr].coords.y - 1; //no overlap so unused
					g->map.list[*p_ptr].ants = 0;
				}
			}
		}
	}
}

void		launch_ants(t_graph *g, t_vector *paths)
{
	int			curr_p;
	int			delta_len;
	uint32_t	*p_ptr;
	t_room		*first_room;

	curr_p = -1;
	while (++curr_p < paths->len)
	{
		if (curr_p = 0
			|| (delta_len = paths->arr[curr_p].len - paths->arr[curr_p - 1].len) <= g->map.list[g->start].ants)
		{
			first_room = &g->map.list[paths->arr[curr_p].dirs[paths->arr[curr_p].len - 1]];
			first_room->ants = g->map.list[g->start].ants--;
			//coords.x
			//coords.y
		}
	}
}

// yolo on copie map comme un porc

void		send_ants(t_graph *g, t_vector *paths)
{
	uint32_t	tot_ants;

	display_map(&g->map, NULL);
	weird_reset_rooms(&g->map);
	tot_ants = g->map.list[g->start].ants;
	while (g->map.list[g->end].ants != tot_ants)
	{
		display_map(&g->map, NULL);
		move_ants(g, paths);
		launch_ants(g, paths);
		ft_printf(
			"####################################################################\n"
			"#######################  ANTS MOVED  ###############################\n"
			"####################################################################\n"
			);
	}
	display_map(&g->map, NULL);
	free(paths->arr);
}