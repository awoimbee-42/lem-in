/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/11 16:01:42 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//use ants to signal if already searched
//cut useless
//

#define MAX_PATHS 256

typedef struct		s_path
{
	uint32_t	len;
	uint32_t	id;
	char		overlaps[4]; // <- 4 overlaps is already quite a bit
	uint8_t		*dirs;
}					t_path;


// def getVoisins(aretes):
//     voisin=[[], [], [], [], [], [], [], [], [], []] #9 listes vides pour les 9 sommets
//     for arete in aretes :
//         voisin[arete[0]].append(arete[1])       #on ajoute les voisins de chaque sommet
//     for v in range(0, len(voisin)):
//         voisin[v].sort()                        #on met les voisins de chaque sommet da
//     return voisin

// def BreadthFirstSearch(aretes):
//     voisins = getVoisins(aretes)
//     fileDAttente = [0]
//     sommetsDejaTraites = []

//     while(fileDAttente): #tant que fileDAttente est pas vide

//         for neighbor in voisins[fileDAttente[0]]:           #pour chaque voisin de du premier sommet de file dattente
//             if neighbor not in fileDAttente and neighbor not in sommetsDejaTraites:
//                 fileDAttente.append(neighbor)               #alors on place Voisin a la fin de la file dattente
//             print(fileDAttente[0],->,neighbor, fileDAttente, sommetsDejaTraites)
//         sommetsDejaTraites.append(fileDAttente.pop(0))      #on supprime le sommet U de la file dattente et le met dans liste sommets deja traites

//     return sommetsDejaTraites

// int			bfs(uint32_t node, t_path *sol, const t_graph *g)
// {
// 	int			i;
// 	int			res;

// 	if (node == g->end)
// 		return (1);
// 	i = 0;
// 	while (i < g->map.list[node].nb_link)
// 	{
// 		if ((res = recurr_bfs(g->map.list[node].links[i], sol, g)))
// 			recurr_win(node, sol);
// 	}


// 	int		goto_node;

// 	goto_node = 0;
// 	while (goto_node < node->map->)


// }

// int			breadth_first(t_graph *graph, t_path *paths)
// {
// 	if (!(paths->dirs = ft_memalloc(graph->map.used * sizeof(*paths->dirs))))
// 		return (-1);

// }

static void		bfs(t_graph *g, int id, t_path *path)
{
	t_queue		*q;
	uint32_t	node;
	uint32_t	tmp;
;
	if (!(q = que_new(g->map.used)) || !que_push(q, g->start))
		exit_lem_in("Could not create queue, bfs cannot continue\n");
	ft_printf("graph start is %s at position %u\n", g->map.list[g->start].name, g->start);
	while (!que_isempty(q))
	{
		if ((node = que_pop(q)) == (t_queued)-1)
			exit_lem_in("Queue shall not be empty, memory corruption ?");
		if (node == g->end)
			ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[node].name);
		ft_printf("{inv}%s<rst> links to :\n", g->map.list[node].name);
		tmp = -1;
		while (++tmp < g->map.list[node].nb_link)
		{
			if (g->map.list[g->map.list[node].links[tmp]].ants != id
				&& g->map.list[node].links[tmp] != g->start)
			{
				ft_printf("\t-> %s\n", g->map.list[g->map.list[node].links[tmp]].name);
				if (!que_push(q, g->map.list[node].links[tmp]))
					exit_lem_in("Could not update queue, memory corruption ?");
				g->map.list[g->map.list[node].links[tmp]].ants = id; // need to check if not visited by other instance
			}
		}
	}
	que_destroy(q);
}

void		find_paths(t_graph *graph)
{
	t_path		paths[256];

	bfs(graph, 1, paths);
}
