/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:00:08 by allespag          #+#    #+#             */
/*   Updated: 2019/04/07 20:35:44 by awoimbee         ###   ########.fr       */
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
	if (string && string->str)
	{
		while (i < string->used)
			ft_memdel((void*)&string->str[i++]);
		ft_memdel((void*)&string->str);
	}
	ft_memdel((void*)&string);
}

void			realloc_t_str(t_str *string)
{
	char		**new_tab;

	if (!(new_tab = malloc(sizeof(char*) * string->size * REALLOC_COEFF)))
		exit_lem_in("Error: malloc (2nd) failed in new_t_str\n");
	ft_mempcpy(new_tab, string->str, string->size * sizeof(*string->str));
	free(string->str);
	string->str = new_tab;
	string->size *= REALLOC_COEFF;
}

t_str			*add_t_str(t_str *string, char *add)
{
	if (string->used == string->size)
		realloc_t_str(string);
	string->str[string->used] = add;
	string->used++;
	return (string);
}

void			display_t_str(t_str *string)
{
	size_t		i;

	i = 0;
	while (i < string->used)
		ft_putendl(string->str[i++]);
}
