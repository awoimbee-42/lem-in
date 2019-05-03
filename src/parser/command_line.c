/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:45:11 by allespag          #+#    #+#             */
/*   Updated: 2019/05/03 16:41:34 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_command		command_hub(t_graph *g, char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (START);
	else if (!ft_strcmp(line, "##end"))
		return (END);
	else if (!ft_strcmp(line, "##red"))
		return (RED);
	else if (!ft_strcmp(line, "##blue"))
		return (BLUE);
	else if (!ft_strcmp(line, "##green"))
		return (GREEN);
	else if (!ft_strcmp(line, "##cyan"))
		return (CYAN);
	else if (!ft_strcmp(line, "##pink"))
		return (PINK);
	else if (!ft_strcmp(line, "##yellow"))
		return (YELLOW);
	else if (!ft_strcmp(line, "##print"))
	{
		g->print = 1;
		return (PRINT);
	}
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

void			exec_room_command(t_room *room, t_command color)
{
	if (color == RED)
		room->color = "{RED}";
	else if (color == BLUE)
		room->color = "{BLU}";
	else if (color == GREEN)
		room->color = "{GRN}";
	else if (color == CYAN)
		room->color = "{CYN}";
	else if (color == PINK)
		room->color = "{PNK}";
	else if (color == YELLOW)
		room->color = "{YLW}";
	else
		room->color = "{wht}";
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
