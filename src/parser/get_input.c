/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:06:22 by allespag          #+#    #+#             */
/*   Updated: 2019/03/19 18:41:31 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// on check la command ou oublie pas, on est pas con hein

void			find_ants(t_graph *g, t_str *str)
{
	char		*line;
	long long	tmp;

	while (1)
	{
		if (get_next_line(0, &line) == -1)
			exit_lem_in("Error: get_next_line failed in find_ants\n");
		if (!line)
			exit_lem_in("ERROR");
		if (is_comment(line))
			str = add_t_str(str, line);
		else if (is_command(line))
		{
			// alors la c'est un peu le bordel pour gerer ca
			// il va avoir des commandes qui parfois passent parfois non
			str = add_t_str(str, line);
		}
		else 
		{
			if (ft_strlen(line) > 11)
				exit_lem_in("ERROR");
			tmp = ft_atoi_pimp(line);
			if (tmp < INT_MIN || tmp > INT_MAX)
				exit_lem_in("ERROR");
			g->ants = (int)tmp;
			str = add_t_str(str, line);
			return ;
		}
	}
}

// DANS FIND_* check line == null
void			get_input(t_graph *g, t_str *str)
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
		str = add_t_str(str, ft_strdup("REMOVE THIS LINE IN CODE PLS"));
	//find_links(g, str, line);
}
