/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:09 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/14 21:37:09 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_del(char *s, char **del, int i, int start)
{
	int	k;

	k = 0;
	while (!ft_is_space(s[i]) && !is_quote(s[i]) && s[i] && s[i++] != '$')
		k++;
	if (s[i - 1] == '$' && is_quote(s[i]))
	{
		*del = NULL;
		return (i);
	}
	else
		*del = ft_substr_m(s, start, start + k);
	return (i);
}

void	find_start_end_for_expand(t_args *a, char *s, char **str)
{
	char	*del;
	char	*get;

	del = NULL;
	get = NULL;
	a->end = a->i;
	a->i++;
	a->exp_start = a->i;
	a->i = find_del(s, &del, a->i, a->exp_start);
	if (del && !(*del)) // for one $
		a->end++;
	*str = ft_strjoin2(*str, s, a->end, a->start);
	a->start = a->end + ft_strlen(del) + 1;
	if (del && !(*del)) //for one $
		(a->start)--;
	if (a->hdoc_flg)
		get = get_env(a->env_lst, del);
	else
		get = get_exp(a->exp_lst, del);
	*str = ft_strjoin2(*str, get, ft_strlen(get), 0);
}

//end is always on '$', start is 0, then it becomes the next of del
void	find_dollar_del(char *s, char **str, t_args *a)
{
	while (s[a->i] && a->i < a->q_idx)
	{
		if ((s[a->i] == '$' && s[a->i + 1] && a->i + 1 < a->q_idx)
			|| (s[a->i] == '$' && a->i + 1 == a->q_idx && !a->hdoc_flg))
		{
			find_start_end_for_expand(a, s, str);
		}
		else
			a->i++;
	}
	if (s[a->i] == '\'' && !a->hdoc_flg) // for $'$HOME'
		a->i--;
}

char	*expand(char *s, t_args *args)
{
	char	*str;

	args->i = -1;
	str = NULL;
	args->start = 0;
	args->hdoc_flg = 0;
	printf("%s\n", s);
	while (s[++args->i])
	{
		if (s[args->i] == '"')
		{
			args->q_idx = find_d_quote2(s, s[args->i], args->i);
			find_dollar_del(s, &str, args);
		}
		else if (s[args->i] == '\'')
			args->i = find_d_quote2(s, s[args->i], args->i);
		else
		{
			args->q_idx = find_d_quotes(s, args->i);
			find_dollar_del(s, &str, args);
		}
	}
	str = ft_strjoin2(str, s, args->i, args->start);
	return (str);
}

char	*hdoc_expand(char *s, t_args *args)
{
	char	*str;

	str = NULL;
	args->i = -1;
	args->start = 0;
	args->hdoc_flg = 1;
	while (s[++args->i])
	{
		args->q_idx = find_d_quotes(s, args->i);
		find_dollar_del(s, &str, args);
	}
	str = ft_strjoin2(str, s, args->i, args->start);
	return (str);
}
