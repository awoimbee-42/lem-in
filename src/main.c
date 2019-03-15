/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:38:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/03/15 21:22:46 by allespag         ###   ########.fr       */
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
	t_graph			*new;
	t_str			*file;

	new = init_graph();
	file = new_t_str(500);
	find_rooms(new, file);
	//parse...
		//get_input(new, file);
		//display_t_str(file);
	//edmon karp...
	return (EXIT_SUCCESS);
}
