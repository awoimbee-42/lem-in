/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:37:38 by awoimbee          #+#    #+#             */
/*   Updated: 2019/05/02 17:34:45 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>

# include <limits.h>
# include <x86intrin.h> //useless ?
# include <inttypes.h>  //useless ?
# include <stdint.h>

# include "libft.h"

# define REALLOC_COEFF 2
# define DEFMALLOCMAP 10
# define DEF_MALLOC_TSTR 10

# define UINT32_NOT_SET 4294967295U

struct s_str;
struct s_map;
struct s_room;
struct s_graph;

typedef enum			e_command
{
	NONE,
	UNKNOWN,
	START,
	END
}						t_command;

typedef struct			s_int2
{
	int				x;
	int				y;
}						t_int2;

typedef struct			s_str
{
	char			**str;
	uint32_t		size;
	uint32_t		used;
}						t_str;

typedef struct			s_map // structure pas forcement utile, complexifie le code pour rien
{
	struct s_room	*list;
	uint32_t		size;
	uint32_t		used;
}						t_map;

typedef struct			s_room
{
	char			*name;
	int				ants;
	t_int2			coords;
	uint32_t		*links;
	uint32_t		nb_link;
	uint32_t		mem_link;
}						t_room;

typedef struct			s_graph
{
	uint32_t		tmp;
	uint32_t		ants;
	uint32_t		start;
	uint32_t		end;
	t_map			map;
}						t_graph;

/*
**	PATHFINDING
*/
void					find_paths(t_graph *graph);
void					send_ants(t_graph *g, t_vector *paths);

/*
**	EXIT
*/
void					exit_lem_in(char *key);
void					exit_clean(t_graph *g, int error);

/*
**	PARSER
*/
void					find_ants(t_graph *g, t_str **str);
void					parse_input(t_graph *g, t_str **str);

/*
**	DEAL_WITH_LINE
*/
long long				ft_atoi_pimp(char *line);
int						ft_atoi_mv_err(const char **nptr, int *err);
int						is_comment(char *line);

/*
**	read_rooms
*/
t_room					*is_room(char *line, t_graph *g);
int						read_rooms(t_graph *g, t_str **str, char **tmp);

/*
**	FIND_LINKS
*/
int						is_link(t_graph *g, t_str **str, char *line);
void					find_links(t_graph *g, t_str **str);

/*
**	COMMAND_LINE
*/
t_command				command_hub(char *line);
void					exec_command(t_graph *g, t_command command);
int						is_command(char *line);

/*
**	T_STR
*/
t_str					*new_t_str(void);
void					free_t_str(t_str *string);
void					realloc_t_str(t_str *string);
void					add_t_str(t_str *string, char *add);
void					display_t_str(t_str *string);

/*
**	T_MAP
*/
t_map					*new_t_map(void);
void					free_t_map(t_map *map, int free_sub);
void					realloc_t_map(t_map *map);
void					add_t_map(t_map *map, t_room *add);
int						is_room_here(t_map *map, t_room *room);

/*
**	LINKS
*/
void					realloc_links(t_room *hub);
void					add_link(t_room *hub, const uint32_t linked);

/*
**	T_ROOM
*/
t_room					*new_room(char *name, int ants, int x, int y);
void					free_room(t_room *room);
int						cmp_room(t_room *a, t_room *b);
void					reset_room(t_room *tmp_room);

/*
**	INIT_GRAPH
*/
t_graph					*init_graph(void);
void					free_t_graph(t_graph *g);

/*
**	DISPLAY_GRAPH_ROOM_MAP (DEBUG)
*/
void					display_links(const t_room *hub, const t_graph *g);
void					display_map(t_map *map, t_graph *maybe_graph);
void					display_room(const t_room *room, const t_graph *g);
void					display_graph(t_graph *g);

#endif
