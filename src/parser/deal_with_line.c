/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:10:08 by allespag          #+#    #+#             */
/*   Updated: 2019/03/16 20:31:36 by allespag         ###   ########.fr       */
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
	if (((line[i] < '0' || line[i] > '9')) && ((line[i] != '-') && line[i] != '+'))
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
