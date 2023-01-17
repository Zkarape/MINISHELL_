/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliT_ani.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:49:14 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/17 18:03:43 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(char *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	*ft_start(char *s, char c)
{
	while (*s)
	{
		if (*s != c)
			return (s);
		s++;
	}
	return (NULL);
}

static char	*ft_end(char *s, char c)
{
	while (*s)
	{
		if (*s != c && ((*(s + 1) == c) || (*(s + 1) == '\0')))
			return (s);
		s++;
	}
	return (NULL);
}

char	**split(char *s, char c)
{
	char	**split;
	int		count;
	int		i;
	int		end;

	count = ft_count(s, c);
	split = ft_calloc((count + 1), sizeof(s));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		s = ft_start(s, c);
		end = ft_end(s, c) - s + 1;
		split[i] = malloc((end + 1) * sizeof(char));
		if (ft_check_alloc(split, split[i], i))
			return (NULL);
		ft_strlcpy(split[i++], s, end + 1);
		s += end;
	}
	return (split);
}
