/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summerize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:13:41 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/02 16:46:22 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_m(char *s, int start, int end)
{
	char	*dst;
	int		i;

	if (!s)
		return (0);
	i = 0;
	dst = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
	{
		dst[i] = s[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	find_last_quote(char *s, char quote)
{
	int	i;

	i = 0;
	while (s[++i])
		if (s[i] == quote)
			return (i);
	return (0);
}

void	more_pipes(char *s)
{
	int	i;

	i = 0;
	if (*s)
	{
		if (*(s) == '|')
			ft_print_error_and_exit("parse error near '|'\n", EXIT_FAILURE);
		while (*s && *s == ' ')
			s++;
		if (*s == '|')
			ft_print_error_and_exit("parse error near '|'\n", EXIT_FAILURE);
	}
}

t_list	*group_until_pipe(char *s)
{
	int		i;
	int		start;
	t_list	*group;

	i = 0;
	start = 0;
	group = lst_construct();
	if (!s)
		return (NULL);
	if (s[0] == '|')
		ft_print_error_and_exit("parse error near '|'\n", EXIT_FAILURE);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i += find_last_quote(&s[i], s[i]);
		else if (s[i] == '|')
		{
			more_pipes(&s[i + 1]);
			lst_add_last(group, ft_substr_m(s, start, i));
			start = i + 1;
		}
		i++;
	}
	lst_add_last(group, ft_substr_m(s, start, i));
	return (group);
}
