/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:05:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/02 16:08:38 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	In this section of the program I repurposed a few variables, so:
**		ants_nb => ant_id
**	And tht's it because we didn't have time to work out overlapping paths
*/

static void		print_ant(uint32_t *is_first_out, int id, const char *room_name)
{
	char	*s;

	s = " L%d-%s";
	if (!*is_first_out && ++s)
		*is_first_out = 1;
	ft_printf(s, id, room_name);
}

static void		weird_reset_rooms(t_map *m)
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

static void		move_ants(t_graph *g, t_vector *paths)
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
			if (g->map.list[*p_ptr].ants != 0)
			{
				if (*(p_ptr - 1) == g->end)
					g->map.list[*(p_ptr - 1)].ants += 1;
				else
					g->map.list[*(p_ptr - 1)].ants = g->map.list[*p_ptr].ants;
				print_ant(&g->ants, g->map.list[*p_ptr].ants,
						g->map.list[*(p_ptr - 1)].name);
				g->map.list[*p_ptr].ants = 0;
			}
		}
	}
}

static void		launch_ants(t_graph *g, t_vector *paths)
{
	int			delta_len;
	t_path		*path_ptr;
	t_path		*last_path;
	t_room		*first_room;

	last_path = &paths->arr[paths->len];
	path_ptr = &paths->arr[-1];
	while (++path_ptr < last_path && g->map.list[g->start].ants > 0)
	{
		if (path_ptr == paths->arr
			|| (delta_len = path_ptr->len - (path_ptr - 1)->len)
			<= g->map.list[g->start].ants)
		{
			first_room = &g->map.list[path_ptr->dirs[path_ptr->len - 1]];
			first_room->ants = g->map.list[g->start].ants--;
			print_ant(&g->ants, first_room->ants, first_room->name);
		}
	}
}

void			send_ants(t_graph *g, t_vector *paths)
{
	int			tot_ants;

	tot_ants = g->ants;
	weird_reset_rooms(&g->map);
	g->map.list[g->start].ants = tot_ants;
	while (g->map.list[g->end].ants != tot_ants)
	{
		g->ants = 0;
		move_ants(g, paths);
		launch_ants(g, paths);
		write(1, "\n", 1);
	}
	tot_ants = -1;
	while ((size_t)++tot_ants < paths->len)
		free(paths->arr[tot_ants].dirs);
	free(paths->arr);
}
