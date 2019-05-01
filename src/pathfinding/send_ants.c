/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:05:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/01 17:58:48 by awoimbee         ###   ########.fr       */
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


// 4 -> 3 -> 2-> 1 -> 0
// 4 = start -> second
// 0 = .. -> end
static void		move_ants(t_graph *g, const t_vector *paths, t_map *nw_m)
{
	uint32_t	room;
	t_room		*nw_room;
	t_path		*p;

	room = -1;
	while (++room != g->map.used)
	{
		if (room == g->start || room == g->end || !g->map.list[room].ants)
			continue ;
		p = &paths->arr[g->map.list[room].coords.x];

		nw_room = &nw_m->list[p->dirs[g->map.list[room].coords.y]];

		if (p->dirs[g->map.list[room].coords.y] != g->end)
		{
			nw_room->ants = g->map.list[room].ants;
			nw_room->coords.x = g->map.list[room].coords.x;
			nw_room->coords.y = g->map.list[room].coords.y - 1;
		}
		else
			nw_room->ants += 1;
	}
}

static void	really_send_ants(t_graph *g, const t_vector *paths, t_map *nw_m)
{
	int			delta_len;
	int			curr_p;

	curr_p = -1;
	while (++curr_p < paths->len)
	{
		if (curr_p == 0 || ())
	}
	while (g->map.list[g->start].ants)
	{

		while ()

	}
}


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

// yolo on copie map comme un porc

void		send_ants(t_graph *g, t_vector *paths)
{
	uint32_t	tot_ants;
	t_map		new_map;

	sizeof(t_room);
	sizeof(__m256)
	display_map(&g->map, NULL);
	weird_reset_rooms(&g->map);
	tot_ants = g->map.list[g->start].ants;
	while (g->map.list[g->end].ants != tot_ants)
	{
		new_map.list = malloc(g->map.used * sizeof(t_room));
		new_map.size = g->map.used;
		new_map.used = g->map.used;
		ft_mempcpy(new_map.list, g->map.list, g->map.used * sizeof(t_room));
		{
			really_send_ants(g, paths, &new_map);
		}
		move_ants(g, paths, &new_map);
		free(g->map.list);
		g->map = new_map;
	}
	// . . . .
	// cost

}