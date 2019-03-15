/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:37:38 by awoimbee          #+#    #+#             */
/*   Updated: 2019/03/15 20:00:16 by allespag         ###   ########.fr       */
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

typedef struct			s_str
{
	char				**str;
	size_t				size;
	size_t				used;
}						t_str;

typedef struct			s_room
{
	char				*name;
	int					ants;
	int					x;
	int					y;
	struct s_room		*linked;
}						t_room;

typedef struct			s_graph
{
	int					ants;
	t_room				*start;
	t_room				*end;
	t_room				*map;
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
**	COMMAND_LINE
*/
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
**	ROOM
*/
t_room					*new_room(char *name, int ants, int x, int y);

/*
**	GRAPH
*/
t_graph					*init_graph(void);

#endif
