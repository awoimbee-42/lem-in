/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:00:17 by allespag          #+#    #+#             */
/*   Updated: 2019/04/08 10:07:05 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <errno.h>

static int		count_spaces(char *line)
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

t_room			*is_room(char *line, t_graph *g)
{
	int			tmp_spaces;
	int			spaces;
	char		*line_ptr;
	t_room		*res;
	int			err;

	spaces = count_spaces(line);
	line_ptr = line;
	if (spaces < 2)                               // mais t'ecris spaces-2<0 au lieu de spaces<2 wtf t'aimes te faire du mal ?
		return (NULL);
	res = new_room(NULL, 0, -1, -1);
	tmp_spaces = 0;
	while (tmp_spaces != spaces - 1)     // while (spaces - count != 1 && tmp[i]) MAIS QUOI
	{
		if (*line_ptr == ' ')
			tmp_spaces++;
		++line_ptr;
	}
	--line_ptr;
	if (!ft_strncat_join(&res->name, line, line_ptr - line))
		exit_lem_in("Error: ft_strncat_join failed in is_room");
	err = 0;
	res->coords.x = ft_atoi_mv_err(&line_ptr, &err);
	res->coords.y = ft_atoi_mv_err(&line_ptr, &err);
	if (err)
	{
		//NORME: remove ce printf
		ft_printf("Error majenta\n");
		free_room(res);
		return (NULL);
	}
	else if (is_room_here(g->map, res))
		exit_lem_in("ERROR");
	return (res);
}

int				find_rooms(t_graph *g, t_str **str, char **tmp) // tmp ??
{
	int			ret;
	char		*line;
	t_command	command;
	t_room		*to_add;

	command = NONE;
	// GNL LEAK ICI
	while ((ret = get_next_line(STDIN_FILENO, &line)) == 1)
	{
		if (is_comment(line))
			add_t_str(*str, line);
		else if (is_command(line))
		{
			command = command_hub(line);
			add_t_str(*str, line);
		}
		else
		{
			if (!(to_add = is_room(line, g)) && (*tmp = line))
				return (1);
			if (command != NONE && command != UNKNOWN) //why even have an 'unknown'?
				exec_command(g, command, to_add);
			add_t_map(g->map, to_add);
			add_t_str(*str, line);
			command = NONE;
			free(to_add);
		}
		// free(line); // unused ?
	}
	// free(line); // unused ?
	if (ret == -1)
		exit_lem_in("Error: get_next_line failed in find_rooms");
	exit_lem_in("end of input in find_rooms");  // to remove
	return (0);
}
