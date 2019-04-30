/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:11:02 by allespag          #+#    #+#             */
/*   Updated: 2019/04/30 17:55:16 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			find_ants(t_graph *g, t_str **str)
{
	char		*line;
	long long	tmp;

	while (1)
	{
		if (get_next_line(0, &line) == -1)
			exit_lem_in("Error: get_next_line failed in find_ants\n");
		if (line == NULL || !ft_strcmp("", line))
			exit_lem_in("ERROR");
		if (is_comment(line) || is_command(line))
			add_t_str(*str, line);
		else
		{
			if (ft_strlen(line) > 11)
				exit_lem_in("ERROR");
			tmp = ft_atoi_pimp(line);
			if (tmp <= 0 || tmp > INT_MAX)
				exit_lem_in("ERROR");
			g->ants = (int)tmp;
			add_t_str(*str, line);
			return ;
		}
	}
}

void			parse_input(t_graph *g, t_str **str)// DANS FIND_* check line == null
{
	int			ret;
	char		*line;

	line = NULL;
	find_ants(g, str);
	ret = read_rooms(g, str, &line);
	if (g->start == UINT32_NOT_SET || g->end == UINT32_NOT_SET)
		exit_lem_in("ERROR (graph has no start or/and no end)");
	if (ret == 0)
		return ;
	else if (ret == 1)
	{
		if (!is_link(g, str, line))
		{
			free(line);
			return ;
		}
		find_links(g, str);
	}
}
