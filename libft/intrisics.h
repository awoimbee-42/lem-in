/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intrisics.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 23:27:57 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/30 02:42:07 by awoimbee         ###   ########.fr       */
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

typedef uint32_t	t_queued;
typedef void		t_listed;

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

#endif
