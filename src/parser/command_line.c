/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:45:11 by allespag          #+#    #+#             */
/*   Updated: 2019/03/15 19:58:26 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//schema de la gestion des commandes
//les return sont a ignores (il faut les changer)
int				command_hub(char *line)
{
	if (!ft_strcmp(line, "start"))
		return (1);
	else if (!ft_strcmp(line, "end"))
		return (1);
	else if (!ft_strcmp(line, "commande inventee dans le cadre des bonus"))
		return (1);
	else			// commande inconnue, on ignore (dunno si ont doit l'add dans l'historique des cmd)
		return (0);
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
