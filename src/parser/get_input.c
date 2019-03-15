/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:06:22 by allespag          #+#    #+#             */
/*   Updated: 2019/03/15 21:00:18 by allespag         ###   ########.fr       */
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

void			get_input(t_graph *g, t_str *str)
{
	find_ants(g, str);
	find_rooms(g, str);
}
