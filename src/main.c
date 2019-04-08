/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:38:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/08 10:18:33 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Peut etre devoir free 2/3 trucs ici
*/
void		exit_lem_in(char *key)
{
	ft_putstr_fd(key, 2);
	exit(EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_graph			*map;
	t_str			*file;

	map = init_graph();
	file = new_t_str();

	parse_input(map, &file);




	display_t_str(file);      // DEBUG

	// find_paths(map);

		// DISPLAY_GRAPH POUR DEBUG
			//display_graph(map);
	//edmon karp...
	free_t_str(file);
	ft_printf("{red}END OF DISPLAY_T_STR\n{eoc}");
	free_t_graph(map);
	ft_printf("{grn}exit sucess well done\n{eoc}");
	return (EXIT_SUCCESS);
}
