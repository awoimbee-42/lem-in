/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:18:13 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/11 14:46:15 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		realloc_links(t_room *hub)
{
	uint		*new_list;

	if (hub->mem_link)
	{
		hub->mem_link *= REALLOC_COEFF;
		if (!(new_list = malloc(sizeof(uint) * hub->mem_link)))
			exit_lem_in("Error: malloc in realloc_links\n");
		ft_mempcpy(new_list, hub->links, hub->nb_link * sizeof(uint));
		free(hub->links);
	}
	else
	{
		hub->mem_link = DEFMALLOCMAP;
		if (!(new_list = malloc(sizeof(uint) * DEFMALLOCMAP)))
			exit_lem_in("Error: malloc in realloc_links\n");
	}
	hub->links = new_list;
}

void		add_link(t_room *hub, const uint linked)
{
	if (hub->nb_link == hub->mem_link)
		realloc_links(hub);
	hub->links[hub->nb_link++] = linked;
}

void		display_links(const t_room *hub, const t_graph *g)
{
	uint	i;

	i = 0;
	while (i < hub->nb_link)
	{
		display_room(&g->map.list[hub->links[i++]], g);
	}
}
