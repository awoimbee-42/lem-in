/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/05 21:49:55 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//use ants to signal if already searched
//cut useless
//

typedef struct		s_path
{
	uint32_t	len;
	char		overlaps[4]; // <- 4 overlaps is already quite a bit
	uint8_t		*dirs;
}					t_path;

typedef union 		u_map_room
{
	t_map		*map;
	t_room		*room;
}					t_map_room;


int			recurr_dfs(t_map_room *node, t_path *sol)
{
	int		goto_node;

	goto_node = 0;
	while (goto_node < node->map->)


}

int			depth_first(t_graph *graph, t_path *paths)
{

	graph->end->ants = 0;
	if (!(paths->dirs = ft_memalloc(512 * sizeof(*paths->dirs))))
		return (-1);






}



void		find_paths(t_graph *graph)
{
	t_path		paths[256];

	depth_first(graph, paths);
}
