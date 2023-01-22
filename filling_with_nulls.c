/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_with_nulls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:27:49 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/22 18:16:57 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filling_without_c(char *s, char c, int len, int count)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	j = 0;
	dst = malloc(sizeof(char) * count + 1);
	while (++i < len)
	{
		if (s[i] != c)
			dst[j++] = s[i];
	}
	dst[j] = '\0';
	return (dst);
}

char	*filling_with_nulls(char *s)
{
	int		i;
	int		len;
	char	quote;
	int		null_count;

	i = -1;
	len = ft_strlen(s);
	null_count = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			s[i] = '\0';
			i += find_last_quote(&s[i], quote);
			s[i] = '\0';
			null_count += 2;
		}
	}
	return (filling_without_c(s, '\0', len, len - null_count));
}

char	*clean_fst_last(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len - 1));
	while (++i < len - 1)
		str[j++] = s[i];
	str[j] = '\0';
	return (str);
}
