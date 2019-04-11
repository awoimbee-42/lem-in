/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:45:11 by allespag          #+#    #+#             */
/*   Updated: 2019/04/11 16:31:58 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//schema de la gestion des commandes
t_command		command_hub(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (START);
	else if (!ft_strcmp(line, "##end"))
		return (END);
	else if (!ft_strcmp(line, "##commande inventee dans le cadre des bonus"))
		return (3);
	else
		return (UNKNOWN);
}

void			exec_command(t_graph *g, t_command command)
{
	if (command == START)
		g->start = g->map.used - 1;
	else if (command == END)
		g->end = g->map.used - 1;
	// else if command == autre chose, bha on peut set la couleur de la room a command
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
