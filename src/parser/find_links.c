/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:19:18 by allespag          #+#    #+#             */
/*   Updated: 2019/03/20 20:59:53 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*find_room_link(t_graph *g, char *ptr, size_t n)
{
	size_t		i;

	i = 0;
	while (i < g->map->used)
	{
		if (!ft_strncmp(ptr, g->map->list[i].name, n))
			return (&g->map->list[i]);
		i++;
	}
	return (NULL);
}

t_room			*get_first_link_part(t_graph *g, char *line)
{
	size_t		i;

	i = 0;
	while (1)
	{
		if (line[i] == '\0')
			return (NULL);
		else if (line[i] == '-')
			break ;
		i++;
	}
	return (find_room_link(g, line, i));
}

t_room			*get_second_link_part(t_graph *g, char *line)
{
	size_t		i;

	i = 0;
	while (1)
	{
		if (line[i] == '\0')
			return (NULL);
		else if (line[i] == '-')
			break ;
		i++;
	}
	return (find_room_link(g, (line + i + 1), ft_strlen(line + i + 1)));
}

int				is_link(t_graph *g, t_str *str, char *line)
{
	t_room		*r1;
	t_room		*r2;

	if (is_comment(line) || is_command(line))
		str = add_t_str(str, line);
	else
	{
		r1 = get_first_link_part(g, line);
		r2 = get_second_link_part(g, line);
		if (!r1 || !r2)
		{
			return (0);
		}
		r1->linked = add_t_map(r1->linked, r2);
		r2->linked = add_t_map(r2->linked, r1);
		ft_putendl("chaussette");
		display_t_str(str);
		str = add_t_str(str, line);
	}
	return (1);
}

void			find_links(t_graph *g, t_str *str)
{
	int			ret;
	char		*line;

	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret == -1)
			exit_lem_in("Error: get_next_line failed in find_links");
		else if (ret == 0 || !line)
			return ;
		else
		{
			if (!is_link(g, str, line))
				return ;
		}
	}
}
