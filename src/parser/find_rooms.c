/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:49:07 by allespag          #+#    #+#             */
/*   Updated: 2019/03/16 22:15:44 by allespag         ###   ########.fr       */
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

// si ce n'est pas une room => check si c'est un tube, si c'est pas le cas
// c'est une ERROR ape
t_room			*is_room(char *line)
{
	int			i;
	int			count;
	int			spaces;
	char		*tmp;
	t_room		*res;
	int			prev_err;

	i = 0;
	count = 0;
	spaces = count_spaces(line);
	tmp = line;
	res = new_room(NULL, -1, -1, -1);
	if (spaces - 2 < 0)
		return (0);
	while (spaces - count != 1 && tmp[i])
	{
		if (tmp[i] == ' ')
			count++;
		i++;
	}
	if(!ft_strncat_join(&res->name, line, i))
		exit_lem_in("Error: ft_strncat_join failed in is_room");
	prev_err = errno;
	tmp = &(tmp[i]);
	// modifier ft_atoi_mv pour ne pas return 0 en cas de nb invalide
	// + ca va peut etre ajouter 2 3 soucis (peut etre falloir avancer les ptr de 1
	res->x = ft_atoi_mv(&tmp);
	res->y = ft_atoi_mv(&tmp);
	if (prev_err != errno)
	{
		room_free(res);
		return (NULL);
	}
	return (res);
}

int				find_rooms(t_graph *g, t_str *str, char **tmp)
{
	int			ret;
	char		*line;
	int			command;
	t_room		*to_add;

	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret == 0)
			return (0);
		else if (ret == -1)
			exit_lem_in("Error: get_next_line failed in find_rooms");
		if (!line)
			return (0);
		if (is_comment(line))
			str = add_t_str(str, line);
		else if (is_command(line))
		{
			command = command_hub(line);
			str = add_t_str(str, line);
		}
		else
		{
			// pas set g->map mais add le resultat de is_room dans g->map:
			if (!((to_add = is_room(line))))
			{
				*tmp = line;
				return (1);
			}
			else
			{
				// gerer la commande, et set la commande a 0 apres
				g->map = add_t_map(to_add);
				str = add_t_str(str, line);
			}
		}
	}
}
