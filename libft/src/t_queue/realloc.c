/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:54:42 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/11 15:10:43 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
		ft_mempcpy(ft_mempcpy(nw_data,
				&q->arr[q->start], (q->size - q->start) * sizeof(t_queued)),
			q->arr, (q->end + 1) * sizeof(t_queued));
	}
	free(q->arr);
	q->size *= 2;
	q->arr = nw_data;
	q->start = 0;
	return (1);
}
