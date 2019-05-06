/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:19:18 by allespag          #+#    #+#             */
/*   Updated: 2019/05/06 15:27:32 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static uint32_t	find_room(t_graph *g, char *name)
{
	uint32_t	i;

	i = 0;
	while (i < g->map.used)
	{
		if (!ft_strcmp(name, g->map.list[i].name))
			return (i);
		i++;
	}
	return (UINT32_NOT_SET);
}

/*
**	We replace '-' with '\0' and use ft_strcmp instead of using ft_strncmp.
**	That is because ft_strncmp("p", "printf", 1) == 0
*/

static uint64_t	get_link(t_graph *g, char *line)
{
	char		*dash;
	uint32_t	res[2];

	dash = line;
	while (*dash && *dash != '-')
		++dash;
	if (!*dash)
		return (INT64_MAX);
	*dash = '\0';
	res[0] = find_room(g, line);
	res[1] = find_room(g, dash + 1);
	*dash = '-';
	return (*(uint64_t*)res);
}

int				is_link(t_graph *g, t_str **str, char *line)
{
	uint32_t	r[2];

	if (!ft_strcmp(line, ""))
		return (0);
	else if (is_comment(line) || is_command(line))
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
