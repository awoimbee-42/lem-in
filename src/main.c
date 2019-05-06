/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:38:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/06 16:12:51 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		exit_lem_in(char *key)
{
	(void)key;
	ft_putstr_fd("ERROR\n", 2);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	exit(EXIT_FAILURE);
}

void		exit_clean(t_graph *g, int error)
{
	free_t_graph(g);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	if (error)
		write(1, "ERROR\n", 6);
	exit(error);
}

int			main(int argc, char **argv)
{
	t_graph			*g;
	t_str			*file;

	if (argc > 1 && !ft_strcmp(argv[1], "--help"))
	{
		ft_printf("Usage: ./lem-in [--p] [--help] < <map_file>\n");
		return (EXIT_SUCCESS);
	}
	g = init_graph();
	if (argc > 1 && (!ft_strcmp(argv[1], "--print")
		|| !ft_strcmp(argv[1], "--p")))
		g->print = 1;
	file = new_t_str();
	parse_input(g, &file);
	find_paths(g, file);
	get_next_line(STDERR_FILENO, GNL_FLUSH);
	free_t_str(file);
	free_t_graph(g);
	return (EXIT_SUCCESS);
}
