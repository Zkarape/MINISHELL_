/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:09 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/20 03:28:23 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_d_quote2(char *s, char quote, int i)
{
	while (s[++i])
		if (s[i] == quote)
			return (i);
	return (0);
}

int	find_d_quotes(char *s, int i)
{
	while (s[i])
	{
		if (is_quote(s[i + 1]) || !s[i + 1])
		{
			if (s[i] == '$')
				return (i + 1);
			return (i);
		}
		i++;
	}
	return (0);
}

char	*get_env(t_env_lst *env_lst, char *del)
{
	t_env	*env_node;
	int		k;

	env_node = env_lst->head->next;
	while (env_node->next && del && *del)
	{
		k = until_equal_sign(&env_node->data[11]);
		if (!ft_strncmp(&env_node->data[11], del, k) && k == ft_strlen(del))
			return (&env_node->data[11 + ft_strlen(del) + 1]);
		env_node = env_node->next;
	}
	return (NULL);
}

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

//end is always on '$', start is 0, then it becomes the next of del
int	find_dollar_del(char *s, char **str, int i, int q_idx, int *start, t_env_lst *env_lst, int hdoc_flg)
{
	int		j;
	int		exp_start;
	char	*del;
	int		end;

	end = 0;
	j = 0;
	exp_start = 0;
	while (s[i] && i < q_idx)
	{
		if ((s[i] == '$' && s[i + 1] && i + 1 < q_idx)
			|| (s[i] == '$' && i + 1 == q_idx && hdoc_flg))
		{
			end = i;
			i++;
			exp_start = i;
			i = find_del(s, &del, i, exp_start);
			if (del && !(*del))// for one $
				end++;
			*str = ft_strjoin(*str, s, end, *start, ft_strlen(*str));
			*start = end + ft_strlen(del) + 1;
			if (del && !(*del))//for one $
				(*start)--;
		//	printf("get_env == %s\n", get_env(env_lst, del));
			*str = ft_strjoin(*str, get_env(env_lst, del),
				ft_strlen(get_env(env_lst, del)), 0, ft_strlen(*str));
		//	printf("str == %s\n", *str);
		}
		else
			i++;
	}
	if (s[i] == '\'')// for $'$HOME'
		return (i - 1);
	return (i);
}

char	*expand(char *s, t_env_lst *env_lst)
{
	int		i;
	int		start;
	char	*str;

	i = -1;
	str = NULL;
	start = 0;
	while (s[++i])
	{
		if (s[i] == '"')
			i = find_dollar_del(s, &str, i,
				find_d_quote2(s, s[i], i), &start, env_lst, 1);
		else if (s[i] == '\'')
			i = find_d_quote2(s, s[i], i);
		else
			i = find_dollar_del(s, &str, i, find_d_quotes(s, i), &start, env_lst, 1);
	}
	str = ft_strjoin(str, s, i, start, ft_strlen(str));
	return (str);
}

char	*hdoc_expand(char *s, t_env_lst *env_lst)
{
	int		i;
	int		start;
	char	*str;

	i = -1;
	str = NULL;
	start = 0;
	while (s[++i])
		i = find_dollar_del(s, &str, i, find_d_quotes(s, i), &start, env_lst, 0);
	str = ft_strjoin(str, s, i, start, ft_strlen(str));
	return (str);
}
