/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:50:19 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:50:34 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *old, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	i;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	ft_bzero(new, new_size);
	i = 0;
	while (old && i < new_size && i < old_size)
	{
		((char *)new)[i] = ((char *)old)[i];
		i++;
	}
	if (old)
		free(old);
	return (new);
}
