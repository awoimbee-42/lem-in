/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:55:10 by allespag          #+#    #+#             */
/*   Updated: 2019/03/19 18:32:28 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph			*init_graph(void)
{
	t_graph		*new;

	if (!(new = (t_graph *)malloc(sizeof(t_graph))))
		exit_lem_in("Error: malloc failed in init_graph\n");
	new->ants = -1;
	new->start = NULL;
	new->end = NULL;
	new->map = new_t_map(10);
	return (new);
}
