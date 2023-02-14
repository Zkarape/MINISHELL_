/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:42:59 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/14 20:59:05 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unquoted(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] != '"')
				return (0);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (0);
		}
		i++;
	}
	return (1);
}

char	*strcpy_noquotes(char *str, char c)
{
	int		i;
	int		j;
	int		count;
	char	*cpy;

	i = -1;
	count = 0;
	j = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	count = ft_strlen(str) - count;
	cpy = malloc(sizeof(char) * count + 1);
	if (!cpy)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] != c)
			cpy[j++] = str[i];
	cpy[j] = '\0';
	return (cpy);
}

char	*removing_fst_lst_dbl_quotes(char *s)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	dst = malloc(sizeof(char) * len - 1);
	while (++i < len - 1)
		dst[i - 1] = s[i];
	dst[i] = '\0';
	return (dst);
}
