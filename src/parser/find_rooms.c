/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:49:07 by allespag          #+#    #+#             */
/*   Updated: 2019/03/15 21:49:55 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
int				is_room(char *line)
{
	int			i;
	int			count;
	int			spaces;
	char		*tmp;

	i = 0;
	count = 0;
	spaces = count_spaces(line);
	tmp = line;
	if (spaces - 2 < 0)
		return (0);
	while (spaces - count != 1 && tmp[i])
	{
		if (tmp[i] == ' ')
			count++;
		i++;
	}
	//reecrire ft_atoi_mv, bien check avant de call du 2nd atoi_mv si tmp[0] = ' ' et si c'est le cas
	//avancer le ptr de 1;
	tmp = &(tmp[i]);
	count = ft_atoi_mv(&tmp);
	ft_printf("1st count = %d\n", count);
	count = ft_atoi_mv(&tmp);
	ft_printf("2nd count = %d\n", count);
	return (1);
}

void			find_rooms(t_graph *g, t_str *str)
{
	int			ret;
	char		*line;
	int			command;

	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret == 0)
			return ;
		else if (ret == -1)
			exit_lem_in("Error: get_next_line failed in find_rooms");
		if (is_comment(line))
			str = add_t_str(str, line);
		else if (is_command(line))
		{
			command = command_hub(line);
			str = add_t_str(str, line);
		}
		else
		{
			is_room(line);
		}
	}
}
