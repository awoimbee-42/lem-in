/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:38:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/05 21:34:43 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// deplacer cette fonction
int			ft_atoi_mv_err(char **nptr, int *err)
{
	short int		sign;
	double			result;
	int				real_result;

	result = 0;
	sign = 1;
	if (**nptr != ' ')
	{
		*err = 1;
		return (0);
	}
	++*nptr;
	if (!ft_isdigit(**nptr) && **nptr != '+' && **nptr != '-')
		*err = 1;
	if (**nptr == '-' && ++*nptr)
		sign = -1;
	else if (**nptr == '+')
		++*nptr;
	while ('0' <= **nptr && **nptr <= '9')
		result = result * 10 + (*(*nptr)++ - 48);
	result *= sign;
	real_result = (int)result;
	if (result != real_result)
		*err = 1;
	return (real_result);
}

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
	file = new_t_str(10);

	parse_input(map, &file);




	display_t_str(file);      // DEBUG

	// find_paths(map);

		// DISPLAY_GRAPH POUR DEBUG
			//display_graph(map);
	//edmon karp...
	free_t_str(file, 1);
	ft_printf("{red}END OF DISPLAY_T_STR\n{eoc}");
	free_t_graph(map);
	ft_printf("{grn}exit sucess well done\n{eoc}");
	return (EXIT_SUCCESS);
}
