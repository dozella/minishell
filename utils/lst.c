/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:03 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 19:16:09 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_create_token(char *value, int key)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	if (!token)
		return (NULL);
	token->key = key;
	token->value = value;
	return (ft_lstnew(token));
}

t_list	*ft_create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc (sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	return (ft_lstnew(env));
}

t_list	*ft_lstnew(void *value)
{
	t_list	*new;

	new = malloc (sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_pushback(t_list **lst, t_list *elem)
{
	t_list	*tmp;

	if (!lst || !elem)
		return ;
	if (!*lst)
	{
		*lst = elem;
		(*lst)->next = NULL;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = elem;
	(tmp->next)->next = NULL;
}
