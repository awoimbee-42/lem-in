/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:19:18 by allespag          #+#    #+#             */
/*   Updated: 2019/04/09 21:04:16 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint32_t		find_room_link(t_graph *g, char *ptr, size_t n)
{
	uint32_t	i;

	i = 0;
	while (i < g->map.used)
	{
		if (!ft_strncmp(ptr, g->map.list[i].name, n))
			return (i);
		i++;
	}
	return (UINT_MAX);
}

uint32_t		get_first_link_part(t_graph *g, char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			return (find_room_link(g, line, i));
		i++;
	}
	return (UINT_MAX);
}

uint32_t			get_second_link_part(t_graph *g, char *line)
{
	while (*line)
	{
		if (*line == '-')
			return (find_room_link(g, line + 1, ft_strlen(line + 1)));
		++line;
	}
	return (UINT_MAX);
}

int				is_link(t_graph *g, t_str **str, char *line)
{
	uint32_t		r1;
	uint32_t		r2;

	if (is_comment(line) || is_command(line))
		add_t_str(*str, line);
	else
	{
		r1 = get_first_link_part(g, line);
		r2 = get_second_link_part(g, line);
		if (r1 == UINT_MAX || r2 == UINT_MAX)
			return (0);
		add_link(&g->map.list[r1], r2);
		add_link(&g->map.list[r2], r1);
		add_t_str(*str, line);
	}
	return (1);
}

void			find_links(t_graph *g, t_str **str)
{
	int			ret;
	char		*line;

	while((ret = get_next_line(STDIN_FILENO, &line)))
	{
		if (ret == -1)
			exit_lem_in("Error: get_next_line failed in find_links");
		if (!is_link(g, str, line))
				return ;
	}
}
