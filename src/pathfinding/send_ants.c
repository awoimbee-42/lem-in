/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:05:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/01 19:57:08 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		weird_reset_rooms(t_map *m)
{
	t_room		*ptr;
	t_room		*map_end;
	t_room		*start;

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
	uint32_t	curr_p;
	uint32_t	*p_ptr;
	uint32_t	*p_start;

	curr_p = -1;
	while (++curr_p < paths->len)
	{
		p_ptr = paths->arr[curr_p].dirs;
		p_start = &paths->arr[curr_p].dirs[paths->arr[curr_p].len];
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
				}

				g->ants = g->ants ?
					ft_printf(" L%d-%s", g->map.list[*p_ptr].ants, g->map.list[*(p_ptr - 1)].name)
					: ft_printf("L%d-%s", g->map.list[*p_ptr].ants, g->map.list[*(p_ptr - 1)].name);
				g->map.list[*p_ptr].ants = 0;
			}
		}
	}
}

void		launch_ants(t_graph *g, t_vector *paths)
{
	uint32_t	curr_p;
	int			delta_len;
	uint32_t	*p_ptr;
	t_room		*first_room;

	curr_p = -1;
	while (++curr_p < paths->len && g->map.list[g->start].ants > 0)
	{
		if (curr_p == 0
			|| (delta_len = paths->arr[curr_p].len - paths->arr[curr_p - 1].len) <= g->map.list[g->start].ants)
		{
			first_room = &g->map.list[paths->arr[curr_p].dirs[paths->arr[curr_p].len - 1]];
			first_room->ants = g->map.list[g->start].ants--;
			//coords.x
			//coords.y
			g->ants = g->ants ?
				ft_printf(" L%d-%s", first_room->ants, first_room->name)
				: ft_printf("L%d-%s", first_room->ants, first_room->name);
		}
	}
}

// yolo on copie map comme un porc

void		send_ants(t_graph *g, t_vector *paths)
{
	int			tot_ants;

	tot_ants = g->ants;
	weird_reset_rooms(&g->map);
	g->map.list[g->start].ants = tot_ants;
	while (g->map.list[g->end].ants != tot_ants)
	{
		g->ants = 0;
		// display_map(&g->map, NULL);
		move_ants(g, paths);
		launch_ants(g, paths);
		write(1, "\n", 1);
	}
	// display_map(&g->map, NULL);
	free(paths->arr);
}