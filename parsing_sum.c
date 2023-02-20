/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/20 14:27:26 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	parsing(char **env_, t_args *args)
{
	char		*s;
	t_list		*lst;
	t_cmd_lst	*cmd_lst;

	s = NULL;
	args->env_lst = getting_env(env_);
	args->exp_lst = env_lst_construct();
	args->exp_lst = exp_cpy_env(args);
	env_lst_add_last(args->exp_lst, "declare -x ?=\"0\"");
	while (1)
	{
		sig_control(1);
		update_status(args);
		free(s);
		s = readline("minishell$ ");
		add_history(s);
		if (!s)
		{
			write(1, "exit\n", 5);
			exit(g_status);
		}
		if (parsing_error_checks(s))
			continue ;
		lst = group_until_pipe(s);
		if (!lst)
		{
			g_status = 1;
			continue ;
		}
		cmd_lst = grouping_with_red(lst, args);
		if (!cmd_lst)
		{
			g_status = 1;
			free_a(args);
			lst_destruct(lst);
			continue ;
		}
		cmd_expanded(cmd_lst, args);
		cmd_quote_clear(cmd_lst);
		if (!cmd_lst->head->no_cmd[0] && cmd_lst->size == 1)
		{
			g_status = 1;
			free_a(args);
			lst_destruct(lst);
			cmd_lst_destruct(cmd_lst, NULL);
			continue ;
		}
		args->env = from_lst_to_dbl(args->env_lst);
		pipex_main(cmd_lst, args);
	}
}

void	cmd_expanded(t_cmd_lst *cmd_lst, t_args *args)
{
	t_cmd	*cur;
	char	*str;
	char	*str1;

	cur = cmd_lst->head;
	str = NULL;
	while (cur)
	{
		str = expand(cur->args, args);
		// printf("args before == %s\n", cur->args);
		free(cur->args);
		cur->args = str;
		// printf("args after == %s\n", cur->args);
		cur = cur->next;
	}
}

char	**no_cmd_clear(char **arr)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (arr[++i])
	{
		str = filling_with_nulls(arr[i]);
		free(arr[i]);
		arr[i] = str;
	}
	arr[i] = NULL;
	return (arr);
}

void	update_status(t_args *a)
{
	t_env	*cur;
	char	*itoa;
	char	*joined;
	char	*duped;

	itoa = NULL;
	joined = NULL;
	cur = a->exp_lst->head->next;
	while (cur->next)
	{
		if (cur->data[11] == '?')
		{
			remove_from_between(cur, a->exp_lst);
			break ;
		}
		cur = cur->next;
	}
	itoa = ft_itoa(g_status);
	duped = ft_strdup("declare -x ?=\""); 
	joined = ft_strjoin3(duped, itoa, "\"");
	env_lst_add_last(a->exp_lst, joined);
	if (joined)
		free(joined);
	if (duped)
		free(duped);
	if (itoa)
		free(itoa);
}

void	printer(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		printf("arr[i] == %s\n", arr[i]);
	}
}

void	cmd_quote_clear(t_cmd_lst *cmd_lst)
{
	t_cmd	*cur;
	char	**arr;
	char	*str;

	cur = cmd_lst->head;
	str = NULL;
	arr = NULL;
	while (cur)
	{
		arr = split(cur->args, ' ');
		if (!arr)
			exit(1);
		cur->no_cmd = no_cmd_clear(arr);
		cur = cur->next;
	}
}
