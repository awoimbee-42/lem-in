/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:38:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/30 20:24:36 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Peut etre devoir free 2/3 trucs ici
*/
void		exit_lem_in(char *key)
{
	ft_putstr_fd(key, 2);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	exit(EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	t_graph			*g;
	t_str			*file;

	(void)argc;
	(void)argv;
	g = init_graph();
	file = new_t_str();
	parse_input(g, &file);
	display_t_str(file);      	// A AJOUTER PARCE QUE C'EST LE SUJET QUI DEMANDE :)
	 ft_printf("{red}END OF DISPLAY_T_STR\n{eoc}");	// A REMOVE
	display_graph(g, 1);								// A REMOVE PARCE QUE C'EST DU DEBUG
	//edmon karp...
	find_paths(g);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	free_t_str(file);
	free_t_graph(g);
	ft_printf("{grn}exit sucess well done\n{eoc}");
	return (EXIT_SUCCESS);
}
