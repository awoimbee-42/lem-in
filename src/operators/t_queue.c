/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_queue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:43:25 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/10 21:27:47 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TO REMOVE: LOTS OF FT_PRINTF

/*
**	Type agnostic, you can safely modify t_queue APPART FROM QUE_DISP!!!
*/

void		que_disp(const t_queue *que)
{
	int			i;

	ft_printf("{YLW}Printing queue at address: %p{eoc}\n", que);
	if (que->start == -1)
	{
		ft_printf("Queue is Empty\n");
		return ;
	}
	if (que->end >= que->start)
	{
		i = que->start - 1;
		while (++i <= que->end)
			ft_printf("%u ", que->arr[i]);
	}
	else
	{
		i = que->start;
		while (i < que->size)
			ft_printf("%u ", que->arr[i++]);
		i = 0;
		while (i <= que->end)
			ft_printf("%u ", que->arr[i++]);
	}
	ft_printf("\n");
}

int			que_realloc(t_queue *q)
{
	t_queued	*nw_data;

	ft_printf("{RED}Realloc circular queue{eoc}\n");
	if (!(nw_data = malloc(q->size * 2 * sizeof(t_queued))))
		return (0);
	if (q->start <= q->end)
	{
		q->end = q->end - q->start;
		ft_mempcpy(nw_data, &q->arr[q->start], (q->end + 1) * sizeof(t_queued));
	}
	else
	{
		ft_mempcpy(nw_data, &q->arr[q->start],
			(q->size - q->start) * sizeof(t_queued));
		ft_mempcpy(&nw_data[q->size - q->start], q->arr,
			(q->end + 1) * sizeof(t_queued));
		q->end = q->size - q->start + q->end;
	}
	free(q->arr);
	q->size *= 2;
	q->arr = nw_data;
	q->start = 0;
	return (1);
}

int			que_push(t_queue *que, t_queued data)
{
	if (que->end == que->size - 1)
	{
		if (que->start == 0 && !que_realloc(que))
			return (0);
		else
			que->end = -1;
	}
	if (que->end == que->start - 1)
		if (!que_realloc(que))
			return (0);
	if (que->start == -1)
		que->start = 0;
	que->arr[++que->end] = data;
	return (1);
}

t_queued	que_pop(t_queue *que)
{
	t_queued	res;

	if (que->start == -1)
		return ((t_queued)-1);
	res = que->arr[que->start++];
	if (que->start == que->size)
		que->start = 0;
	if (que->start == que->end + 1)
	{
		que->start = -1;
		que->end = -1;
	}
	return (res);
}

t_queue		*que_new(size_t len)
{
	t_queue		*que;

	if (!(que = malloc(sizeof(t_queue)))
		|| !(que->arr = malloc(len * sizeof(t_queued))))
		return (NULL);
	que->start = -1;
	que->end = -1;
	que->size = len;
	return (que);
}

void		que_destroy(t_queue *que)
{
	free(que->arr);
	free(que);
}

int			que_is_empty(const t_queue *que)
{
	if (que->start == -1)
		return (1);
	return (0);
}