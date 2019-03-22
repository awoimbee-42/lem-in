/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:12:57 by allespag          #+#    #+#             */
/*   Updated: 2019/03/22 20:03:08 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_str			*new_t_str(size_t size)
{
	t_str		*new;

	if (!(new = (t_str *)malloc(sizeof(t_str))))
		exit_lem_in("Error: malloc (1st) failed in new_t_str\n");
	if (!(new->str = (char **)malloc(sizeof(char *) * size)))
	{
		free(new);
		exit_lem_in("Error: malloc (2nd) failed in new_t_str\n");
	}
	new->size = size;
	new->used = 0;
	return (new);
}

void			free_t_str(t_str *string)
{
	size_t		i;

	i = 0;
	if (string)
	{
		if (string->str)
		{
			while (i < string->used)
			{
				free(string->str[i]);
				i++;
			}
			free(string->str);
		}
		free(string);
	}
}

t_str			*realloc_t_str(t_str *string)
{
	size_t		i;
	t_str		*new;

	i = 0;
	new = new_t_str(string->size * 2);
	new->used = string->used;
	while (i < string->size)
	{
		new->str[i] = string->str[i];
		i++;
	}
	return (new);
}

t_str			*add_t_str(t_str *string, char *add)
{
	t_str		*tmp;

	if (string->used >= string->size)
	{
		tmp = realloc_t_str(string);
	//	free_t_str(string);
		tmp->str[tmp->used] = add;
		tmp->used++;
		return (tmp);
	}
	string->str[string->used] = add;
	string->used++;
	return (string);
}

void			display_t_str(t_str *string)
{
	size_t		i;

	i = 0;
	if (string->used >= string->size)
		ft_printf("{red}[%d] %d < %d\n{eoc}", (i < string->used), i, string->used);
	while (i < string->used)
	{
		ft_putendl(string->str[i]);
		i++;
	}
}
