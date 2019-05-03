/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:38:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/03 15:06:37 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//	Peut etre devoir free 2/3 trucs ici

void		exit_lem_in(char *key) // QUAND ON PRINT ERROR, ON LE FAIT SUR STDERR OU STDOUT?
{
	ft_putstr_fd(key, 2);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	exit(EXIT_FAILURE);
}

void		exit_clean(t_graph *g, int error)
{
	free_t_graph(g);
	if (error)
		write(1, "ERROR\n", 6);
	exit(error);
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
	// display_t_str(file);
	ft_printf("{red}END OF DISPLAY_T_STR\n{eoc}");
	find_paths(g, file);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	free_t_str(file);
	free_t_graph(g);
	ft_printf("{grn}exit sucess well done\n{eoc}");
	return (EXIT_SUCCESS);
}
