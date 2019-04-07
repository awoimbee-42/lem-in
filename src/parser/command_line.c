/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:45:11 by allespag          #+#    #+#             */
/*   Updated: 2019/04/08 00:45:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//schema de la gestion des commandes
//les return sont a ignores (il faut les changer)
t_command		command_hub(char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (START);
	else if (!ft_strcmp(line, "##end"))
		return (END);
	else if (!ft_strcmp(line, "##commande inventee dans le cadre des bonus"))
		return (3);
	else			// commande inconnue, on ignore (dunno si ont doit l'add dans l'historique des cmd)
		return (UNKNOWN);
}

void			exec_command(t_graph *g, int command, t_room *to_set)
{
	if (command == START)
		g->start = to_set;
	else if (command == END)
		g->end = to_set;
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
