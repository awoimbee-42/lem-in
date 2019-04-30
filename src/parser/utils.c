/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:10:08 by allespag          #+#    #+#             */
/*   Updated: 2019/04/30 16:15:50 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

long long			ft_atoi_pimp(char *line)
{
	int				i;
	int				sign;
	long long		res;

	i = 0;
	sign = 1;
	res = 0;
	// NORM NORM NORM : mbenjell serait content de ca ou pas ?
	if ((line[i] < '0' || line[i] > '9')
			&& ((line[i] != '-') && line[i] != '+'))
		exit_lem_in("ERROR");
	if (line[i] == '-' || line[i] == '+')
	{
		sign = ((line[i] == '-') ? -1 : 1);
		i++;
	}
	while (line[i] >= '0' && line[i] <= '9')
	{
		res = (res * 10) + line[i] - '0';
		i++;
	}
	if (line[i] || ((line[0] == '+' || line[0] == '-') && !line[1]))
		exit_lem_in("ERROR");
	return (sign * res);
}

int					is_comment(char *line)
{
	if (!ft_strcmp(line, ""))
		exit_lem_in("ERROR");
	else if (line[0] == '#' && line[1] != '#')
		return (1);
	return (0);
}

int					ft_atoi_mv_err(const char **nptr, int *err)
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
