/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:06:22 by allespag          #+#    #+#             */
/*   Updated: 2019/03/22 20:16:10 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TOI QUI FAIS LA NORME : check si ants <= 0 ^^^^^^^^^
void			find_ants(t_graph *g, t_str **str)
{
	char		*line;
	long long	tmp;

	while (1)
	{
		if (get_next_line(0, &line) == -1)
			exit_lem_in("Error: get_next_line failed in find_ants\n");
		if (!line)
			exit_lem_in("ERROR");
		if (is_comment(line) || is_command(line))
			add_t_str(*str, line);
		else
		{
			if (ft_strlen(line) > 11)
				exit_lem_in("ERROR");
			tmp = ft_atoi_pimp(line);               // MAIS FDP DE TES MORTS CA FONCTIONNE PAS CA, C'EST LE MEILLEUR MOYEN DE SE TAPER UN CRASH CHELOU
			if (tmp < INT_MIN || tmp > INT_MAX)     // :((((
				exit_lem_in("ERROR");               // whyyyyyyyyyyyyyy u do dis
			g->ants = (int)tmp;
			add_t_str(*str, line);
			return ;
		}
	}
}

// DANS FIND_* check line == null
void			parse_input(t_graph *g, t_str **str)
{
	int			ret;
	char		*line;

	line = NULL;
	find_ants(g, str);
	ret = find_rooms(g, str, &line);
	// TOI QUI FAIT LA NORME, N'OUBLIE PAS DE CHANGER LE MESSAGE DU EXIT_LEM_IN SUIVANT APE
	if (g->start == NULL || g->end == NULL)
		exit_lem_in("ERROR (no start or/and no end)");
	if (ret == 0)
		return ;
	else if (ret == 1)
	{
		if (!is_link(g, str, line))
			return ;
		find_links(g, str);
	}
}
