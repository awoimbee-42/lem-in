/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:00:17 by allespag          #+#    #+#             */
/*   Updated: 2019/05/02 00:57:08 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <errno.h>

static int		count_spaces(const char *line)
{
	int			count;

	count = 0;
	while (*line)
	{
		if (*line == ' ')
			count++;
		++line;
	}
	return (count);
}

//
//	NORM:
//
//	TO REMOVE / OR MODIFY
//	if (spaces)
//	{
//		ft_printf("...");
//		return (0);
//	}
//

static int		add_new_room(const char *line, t_graph *g)
{
	int			spaces;
	t_room		tmp_room;
	const char	*line_iter;

	if ((spaces = count_spaces(line)) < 2)
	{
		ft_printf("line = '%s'\n", line);
		ft_printf("{GRN}Error green -- spaces == %d < 2{eoc}\n", spaces);
		return (0);
	}
	line_iter = line;
	while (spaces != 1)
	{
		if (*line_iter == ' ')
			--spaces;
		++line_iter;
	}
	--line_iter;
	reset_room(&tmp_room);
	if (!ft_strncat_join(&tmp_room.name, line, line_iter - line))
		exit_lem_in("Error: ft_strncat_join failed in is_room");
	spaces = 0;
	tmp_room.coords.x = ft_atoi_mv_err(&line_iter, &spaces);
	tmp_room.coords.y = ft_atoi_mv_err(&line_iter, &spaces);
	if (spaces)
	{
		ft_printf("{RED}Error majenta -- coordonnes de merde >> JE FREE UN TRUC ICI{eoc}\n");
		free(tmp_room.name);
		return (0);
	}
	else if (is_room_here(&g->map, &tmp_room) || line[0] == 'L')
	{
		ft_printf("{CYN}Error cyan -- room_is_here OR line[0] == 'L'\n{eoc}");
		return (0);
	}
	add_t_map(&g->map, &tmp_room);
	return (1);
}

int				read_rooms(t_graph *g, t_str **str, char **last_line)
{
	int			ret;
	t_command	cmd;

	cmd = NONE;
	while ((ret = get_next_line(STDIN_FILENO, last_line)) == 1)
	{
		if (!ft_strcmp(*last_line, ""))
			return (0);
		else if (is_comment(*last_line))
			add_t_str(*str, *last_line);
		else if (is_command(*last_line) && ((cmd = command_hub(*last_line))))
			add_t_str(*str, *last_line);
		else
		{
			if (!add_new_room(*last_line, g))
				return (1);
			if (cmd != NONE && cmd != UNKNOWN)
				exec_command(g, cmd);
			add_t_str(*str, *last_line);
			cmd = NONE;
		}
	}
	if (ret == -1)
		exit_lem_in("Error: get_next_line failed in read_rooms");
	return (0);
}
