/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:00:17 by allespag          #+#    #+#             */
/*   Updated: 2019/04/05 21:56:03 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <errno.h>

static int		count_spaces(char *line)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

t_room			*is_room(char *line, t_graph *g)
{
	int			i;
	int			count;
	int			spaces;
	char		*tmp;
	t_room		*res;
	int			err;

	i = 0;
	count = 0;
	spaces = count_spaces(line);
	tmp = line;
	if (spaces - 2 < 0)
		return (NULL);
	res = new_room(NULL, 0, -1, -1);
	while (spaces - count != 1 && tmp[i])
	{
		if (tmp[i] == ' ')
			count++;
		i++;
	}
	if (!ft_strncat_join(&res->name, line, i - 1))
		exit_lem_in("Error: ft_strncat_join failed in is_room");
	err = 0;
	tmp = &(tmp[i - 1]);
	res->coords.x = ft_atoi_mv_err(&tmp, &err);
	res->coords.y = ft_atoi_mv_err(&tmp, &err);
	if (err)
	{
		//NORME: remove ce printf
		ft_printf("Error majenta\n");
		room_free(res);
		return (NULL);
	}
	else if (is_room_here(g->map, res))
		exit_lem_in("ERROR");
	return (res);
}

int				find_rooms(t_graph *g, t_str **str, char **tmp)
{
	int			ret;
	char		*line;
	int			command;
	t_room		*to_add;

	command = 0;
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret == -1)
			exit_lem_in("Error: get_next_line failed in find_rooms");
		else if (ret == 0 || !line)
		{
			//NORME: remove ce printf
			ft_printf("ret == 0 || !line\n");
			return (0);
		}
		if (is_comment(line))
			*str = add_t_str(*str, line);
		else if (is_command(line))
		{
			command = command_hub(line);
			*str = add_t_str(*str, line);
		}
		else
		{
			if (!((to_add = is_room(line, g))))
			{
				*tmp = line;
				return (1);
			}
			else
			{
				if (command > 0)
					exec_command(g, command, to_add);
				g->map = add_t_map(g->map, to_add);
				*str = add_t_str(*str, line);
				command = 0;
				free(to_add);
			}
		}
	}
}
