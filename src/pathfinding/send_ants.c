/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:05:34 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/03 16:21:46 by awoimbee         ###   ########.fr       */
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
		p_ptr = &paths->arr[curr_p].dirs[paths->arr[curr_p].len - 1];
		p_start = &paths->arr[curr_p].dirs[0];
		while (--p_ptr >= p_start)
		{
			if (g->map.list[*p_ptr].ants != 0)
			{
				if (*(p_ptr + 1) == g->end) //sdsdsdsd
					g->map.list[*(p_ptr + 1)].ants += 1;
				else
					g->map.list[*(p_ptr + 1)].ants = g->map.list[*p_ptr].ants; //sdsdsds
				print_ant(&g->tmp, g->map.list[*p_ptr].ants,
						g->map.list[*(p_ptr + 1)].name); //sdsdsdsddsd
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
	while (++path_ptr < last_path && g->map.list[g->start].ants > 0
		&& (path_ptr == paths->arr
			|| (delta_len = path_ptr->len - (path_ptr - 1)->len)
			<= g->map.list[g->start].ants))
	{
		first_room = &g->map.list[path_ptr->dirs[0]];
		first_room->ants = g->ants - --g->map.list[g->start].ants;
		print_ant(&g->tmp, first_room->ants, first_room->name);
	}
}

void			calc_ants_to_launch(t_graph *g, t_vector *vec)
{
	uint32_t	i;
	uint32_t	paths_len_sum;
	int			ants_launched;

	ants_launched = 0;
	paths_len_sum = 0;
	i = -1;
	while (++i < vec->len)
		paths_len_sum += vec->arr[i].len;

	i = -1;
	while (++i < vec->len)
	{
		ft_printf("vec->arr[i].ants_to_lanch = (%u - ((%u - 1) * %u - (%u - %u))) / %u;\n", g->ants, vec->len - 1, vec->arr[i].len, paths_len_sum, vec->arr[i].len, vec->len);
		vec->arr[i].ants_to_lanch = ((int)g->ants - (((int)vec->len - 1) * (int)vec->arr[i].len - ((int)paths_len_sum - (int)vec->arr[i].len))) / (int)vec->len;
		ants_launched += vec->arr[i].ants_to_lanch;
		ft_printf("{PNK}paths %u, len %u, ants to launch %d{eoc}\n", i, vec->arr[i].len, vec->arr[i].ants_to_lanch);
	}
	if (ants_launched != (int)g->ants)
		ft_printf("FUUUUUUCK %d\n", ants_launched - (int)g->ants);
}

void			send_ants(t_graph *g, t_vector *paths)
{
	int			tot_ants;
	uint32_t	line_nb;

	line_nb = 0;
	tot_ants = g->ants;
	weird_reset_rooms(&g->map);
	calc_ants_to_launch(g, paths);
	g->map.list[g->start].ants = tot_ants;
	while (g->map.list[g->end].ants != tot_ants)
	{
		g->tmp = 0;
		move_ants(g, paths);
		launch_ants(g, paths);
		write(1, "\n", 1);
		++line_nb;
	}
	tot_ants = -1;
	while ((size_t)++tot_ants < paths->len)
		free(paths->arr[tot_ants].dirs);
	free(paths->arr);
	ft_printf("<bold>{RED}%d lines<rst>\n", line_nb);
}
