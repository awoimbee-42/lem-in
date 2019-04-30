/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intrisics.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 23:27:57 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/30 20:01:31 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LFT_INTRISICS_H
# define LFT_INTRISICS_H
# include <inttypes.h>
# include <string.h>
# include <x86intrin.h>

# ifdef __AVX__
#  define LFT_AVX 1
#  else
#  define LFT_AVX 0
# endif

# define GNL_BUFF_SIZE 300
# define GNL_FLUSH (char**)INTPTR_MAX

/*
**	lem-in specific struct
*/

typedef struct		s_path
{
	uint32_t	len;
	int			overlaps[2];
	uint32_t	*dirs;
}					t_path;

typedef uint32_t	t_queued;
typedef void		t_listed;
typedef t_path		t_vected;

typedef struct	s_list
{
	t_listed		*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_queue
{
	int				start;
	int				end;
	int				size;
	t_queued		*arr;
}				t_queue;

typedef union	u_vec4
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	}				flt;
	__m128			sse __attribute__((aligned(16)));
}				t_vec4;

typedef struct	s_vector
{
	t_vected		*arr;
	size_t			len;
	size_t			mem;
}				t_vector;

#endif
