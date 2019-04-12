/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:54 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/12 16:53:12 by awoimbee         ###   ########.fr       */
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
	char		overlaps[4]; // <- 4 overlaps is already quite a bit
	uint32_t	*dirs;
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

static void		bfs(t_graph *g, int id, t_path *paths)
{
	t_queue		*q;
	uint32_t	node;
	uint32_t	tmp;
	uint32_t	*parents;

	if (!(q = que_new(g->map.used)) || !que_push(q, g->start))
		exit_lem_in("Could not create queue, bfs cannot continue\n");
	if (!(parents = ft_memalloc(g->map.used * sizeof(uint32_t))))
		exit_lem_in("Could not allocate memory in bfs() for parents");

	ft_printf("graph start is %s at position %u\n", g->map.list[g->start].name, g->start);
	while (!que_isempty(q))
	{
		if ((node = que_pop(q)) == (t_queued)-1)
			exit_lem_in("Queue shall not be empty, memory corruption ?");

		// if (paths[id].len != 0 && node == paths[id].dirs[paths[id].len - 1])
		// 	paths[id].len--;
		// else
		// 	paths[id].len++;
		// paths[id].dirs[paths[id].len - 1] = node;


		if (node == g->end)
		{
			ft_printf("{ylw}end (%s) found, well done !{eoc}\n", g->map.list[node].name);
			for (uint32_t r = g->end; r != g->start; r = parents[r])
				ft_printf("{blu}%s <-- {eoc}", g->map.list[r].name);
			ft_printf("\n\n\n");

			// ft_mempcpy(paths[id + 1].dirs, paths[id].dirs, paths[id].len * sizeof(*paths->dirs));
			// paths[id + 1].len = paths[id].len;
			// // paths[id].overlaps // duno what to do with dis
			// ++id;
			continue ;
		}
		ft_printf("{inv}%s<rst> links to :\n", g->map.list[node].name);
		tmp = -1;
		while (++tmp < g->map.list[node].nb_link)
		{
			ft_printf("\t-> %s\n", g->map.list[g->map.list[node].links[tmp]].name);
			if (g->map.list[g->map.list[node].links[tmp]].ants == 0
				&& g->map.list[node].links[tmp] != g->start)
			{
				parents[g->map.list[node].links[tmp]] = node;
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
	t_path		*paths;

	paths = &((t_path*)ft_memalloc(sizeof(*paths) * 256))[-1];
	int i = 0;
	while (++i <= 256)
		paths[i].dirs = malloc(graph->map.used * sizeof(*paths[i].dirs));
	bfs(graph, 1, paths);
	ft_printf("{PNK}END OF BFS, PATHS:{eoc}\n");
	for (t_path *p = &paths[1]; p->len != 0; ++p)
	{
		for (uint32_t xyz = 0; xyz < p->len; ++xyz)
			ft_printf("-->%s\n", graph->map.list[p->dirs[xyz]].name);
		ft_printf("\n\n");
	}


}
