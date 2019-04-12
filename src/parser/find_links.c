/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:19:18 by allespag          #+#    #+#             */
/*   Updated: 2019/04/12 17:10:35 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static uint32_t	find_room_link(t_graph *g, char *ptr, size_t n)
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

static uint64_t	get_link(t_graph *g, char *line)
{
	uint32_t	i;
	uint32_t	res[2];

	i = 0;
	while (line[i] && line[i] != '-')
		++i;
	if (!line[i])
		return (INT64_MAX);
	res[0] = find_room_link(g, line, i);
	++i;
	res[1] = find_room_link(g, line + i, ft_strlen(line + i));
	return (*(uint64_t*)res);
}

int				is_link(t_graph *g, t_str **str, char *line)
{
	uint32_t	r[2];

	if (is_comment(line) || is_command(line))
		add_t_str(*str, line);
	else
	{
		*(uint64_t*)r = get_link(g, line);
		if (r[0] == UINT_MAX || r[1] == UINT_MAX)
			return (0);
		add_link(&g->map.list[r[0]], r[1]);
		add_link(&g->map.list[r[1]], r[0]);
		add_t_str(*str, line);
	}
	return (1);
}

void			find_links(t_graph *g, t_str **str)
{
	int			ret;
	char		*line;

	while ((ret = get_next_line(STDIN_FILENO, &line)) == 1)
	{
		if (!is_link(g, str, line))
			return ;
	}
	if (ret == -1)
		exit_lem_in("Error: get_next_line failed in find_links");
}
