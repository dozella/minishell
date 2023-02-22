/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:50:22 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:50:34 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_char(char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	in_word;
	int	n_words;

	i = 0;
	in_word = 0;
	n_words = 0;
	while (str[i])
	{
		if (!in_word && !ft_is_char(str[i], c))
		{
			n_words += 1;
			in_word = 1;
		}
		else if (in_word && ft_is_char(str[i], c))
			in_word = 0;
		i++;
	}
	return (n_words);
}

static char	*ft_h(char *str, const char *s, int len, int start)
{
	str = (char *)malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}

static void	make_words(char const *s, char **strs, char c, int in_word)
{
	int		i;
	int		n_words;
	int		start;

	i = -1;
	n_words = 0;
	while (s[++i])
	{
		if (!in_word && !ft_is_char(s[i], c))
		{
			start = i;
			n_words += 1;
			in_word = 1;
		}
		if (in_word && ft_is_char(s[i], c))
		{
			in_word = 0;
			strs[n_words - 1] = ft_h(strs[n_words - 1],
					s, i - start + 1, start);
		}
	}
	if (in_word)
		strs[n_words - 1] = ft_h(strs[n_words - 1], s, i - start + 1, start);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;

	words = count_words(s, c);
	strs = (char **)malloc (sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	make_words(s, strs, c, 0);
	strs[words] = NULL;
	return (strs);
}
