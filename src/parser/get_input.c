/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:11:02 by allespag          #+#    #+#             */
/*   Updated: 2019/05/06 16:26:54 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_line_exit(t_graph *g, char *line)
{
	free(line);
	exit_clean(g, 1);
}

void			find_ants(t_graph *g, t_str **str)
{
	char		*line;
	long long	tmp;

	while (1)
	{
		if (get_next_line(0, &line) == -1)
			exit_clean(g, 1);
		if (line == NULL || !ft_strcmp("", line))
			free_line_exit(g, line);
		if (is_comment(line) || is_command(line))
			add_t_str(*str, line);
		else
		{
			if (ft_strlen(line) > 11)
				free_line_exit(g, line);
			tmp = ft_atoi_pimp(line);
			if (tmp <= 0 || tmp > INT_MAX)
				free_line_exit(g, line);
			g->ants = (int)tmp;
			add_t_str(*str, line);
			return ;
		}
	}
}

void			parse_input(t_graph *g, t_str **str)
{
	int			ret;
	char		*line;

	line = NULL;
	find_ants(g, str);
	ret = read_rooms(g, str, &line);
	if (g->start == UINT32_NOT_SET || g->end == UINT32_NOT_SET || !ret)
	{
		free(line);
		free_t_str(*str);
		exit_clean(g, 1);
	}
	else if (ret == 1)
	{
		if (!is_link(g, str, line))
		{
			free(line);
			free_t_str(*str);
			exit_clean(g, 1);
		}
		find_links(g, str);
	}
}
