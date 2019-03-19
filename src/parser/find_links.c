/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:19:18 by allespag          #+#    #+#             */
/*   Updated: 2019/03/19 18:57:58 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			find_links(t_graph *g, t_str *str, char **tmp)
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
		if (is_comment(line))
			str = add_t_str(str, line);
		// peut etre changer la gestion de la commande pour le tubes
		//	UPDATE : LES COMMANDES SONT IGNOREES ICI
		else if (is_command(line))
			continue ;
		else
		{
			// ajoute le link dans les 2 sens, pour n1 et n2
		}

	}
}
