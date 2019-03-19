/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:37:38 by awoimbee          #+#    #+#             */
/*   Updated: 2019/03/19 18:36:14 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>

# include <limits.h>
# include <x86intrin.h>
# include <inttypes.h>

# include "libft.h"

# define START 1
# define END 2
# define UNKNOWN -1

struct					s_str;
struct					s_map;
struct					s_room;
struct					s_graph;

typedef struct			s_str
{
	char				**str;
	size_t				size;
	size_t				used;
}						t_str;

typedef struct			s_map
{
	struct s_room		*list;
	size_t				size;
	size_t				used;
}						t_map;

typedef struct			s_room
{
	char				*name;
	int					ants;
	int					x;
	int					y;
	t_map				*linked;
}						t_room;

typedef struct			s_graph
{
	int					ants;
	t_room				*start;
	t_room				*end;
	t_map				*map;
}						t_graph;

// PROTEGER : ./lem-in < /dev/zero putain d'arthur de con (le /dev/random est protege mais random je pense)

/*
**	EXIT
*/
void					exit_lem_in(char *key);

/*
**	PARSER
*/
void					find_ants(t_graph *g, t_str *str);
void					get_input(t_graph *g, t_str *str);

/*
**	DEAL_WITH_LINE
*/
long long				ft_atoi_pimp(char *line);
int						is_comment(char *line);

/*
**	FIND_ROOMS
*/
t_room					*is_room(char *line, t_graph *g);
int						find_rooms(t_graph *g, t_str *str, char **tmp);

/*
**	COMMAND_LINE
*/
int						command_hub(char *line);
void					exec_command(t_graph *g, int command, t_room *to_set);
int						is_command(char *line);

/*
**	T_STR
*/
t_str					*new_t_str(size_t size);
void					free_t_str(t_str *string);
t_str					*realloc_t_str(t_str *string);
t_str					*add_t_str(t_str *string, char *add);
void					display_t_str(t_str *string);

/*
**	T_MAP
*/
t_map					*new_t_map(size_t size);
void					free_t_map(t_map *map);
t_map					*realloc_t_map(t_map *map);
t_map					*add_t_map(t_map *map, t_room *add);
int						is_room_here(t_map *map, t_room *room);

/*
**	INIT_ROOM
*/
t_room					*new_room(char *name, int ants, int x, int y);
void					room_free(t_room *room);
int						cmp_room(t_room *a, t_room *b);

/*
**	INIT_GRAPH
*/
t_graph					*init_graph(void);

#endif
