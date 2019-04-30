/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:45:11 by allespag          #+#    #+#             */
/*   Updated: 2019/04/30 15:39:48 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_command		command_hub(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (START);
	else if (!ft_strcmp(line, "##end"))
		return (END);
	else
		return (UNKNOWN);
}

void			exec_command(t_graph *g, t_command command)
{
	if (command == START)
		g->start = g->map.used - 1;
	else if (command == END)
		g->end = g->map.used - 1;
}

int				is_command(char *line)
{
	size_t		safe;

	safe = ft_strlen(line);
	if (safe < 2)
		return (0);
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}
