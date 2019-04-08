/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:37:38 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/08 10:21:10 by awoimbee         ###   ########.fr       */
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

# define REALLOC_COEFF 2
# define DEF_MALLOC_MAP 10
# define DEF_MALLOC_TSTR 10

struct					s_str;
struct					s_map;
struct					s_room;
struct					s_graph;

typedef enum	e_command
{
	UNKNOWN,  // ca c'est inutile nn ?
	NONE,     // et avec ca c'est un peu redondant
	START,
	END
}				t_command;

typedef struct			s_int2
{
	int				x; // des int 16 bits ca serait cool ici
	int				y;
}						t_int2;

typedef struct			s_str
{
	char			**str;
	uint32_t		size;
	uint32_t		used;
}					t_str;

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
	t_map			linked;   // c'est plus un putain depointeur de merde :) *suicide*
	//t_map			*links;
	//uint32_t		nb_link;
	//uint32_t		mem_link;
}						t_room;

typedef struct			s_graph
{
	int				ants;			// ants_nb
	t_room			*start;
	t_room			*end;
	t_map			*map;			// Ca mene a quelle room ca ? ca sert a quoi ?
}						t_graph;


/*
**	EXIT
*/
void					exit_lem_in(char *key);

/*
**	PARSER
*/
void					find_ants(t_graph *g, t_str **str);
void					parse_input(t_graph *g, t_str **str);

/*
**	DEAL_WITH_LINE
*/
long long				ft_atoi_pimp(char *line);
int						ft_atoi_mv_err(char **nptr, int *err);
int						is_comment(char *line);

/*
**	FIND_ROOMS
*/
t_room					*is_room(char *line, t_graph *g);
int						find_rooms(t_graph *g, t_str **str, char **tmp);

/*
**	FIND_LINKS
*/
t_room					*find_room_link(t_graph *g, char *ptr, size_t n);
t_room					*get_first_link_part(t_graph *g, char *line);
t_room					*get_second_link_part(t_graph *g, char *line);
int						is_link(t_graph *g, t_str **str, char *line);
void					find_links(t_graph *g, t_str **str);

/*
**	COMMAND_LINE
*/
t_command				command_hub(char *line);
void					exec_command(t_graph *g, int command, t_room *to_set);
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
**	INIT_ROOM
*/
t_room					*new_room(char *name, int ants, int x, int y);
void					free_room(t_room *room);
int						cmp_room(t_room *a, t_room *b);

/*
**	INIT_GRAPH
*/
t_graph					*init_graph(void);
void					free_t_graph(t_graph *g);

/*
**	DISPLAY_GRAPH_ROOM_MAP (DEBUG)
*/
void					display_map(t_map *map);
void					display_room(t_room *room, int map);
void					display_graph(t_graph *g);

#endif
