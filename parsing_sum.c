/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/14 21:46:37 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//	env_lst_print(args->exp_lst);
	while (1)
	{
		sig_control(1);
		s = readline("minishell$ ");
		if (g_status == 1)
		{
			g_status = -2;
			continue ;
		}
		if (!s)
		{
			write(1, "exit\n", 5);
			exit(g_status);
		}
		parsing_error_checks(s);
		if (*s)
			add_history(s);
		lst = group_until_pipe(s);
		if (!lst)
			continue ;
		cmd_lst = grouping_with_red(lst, args);
		if (!cmd_lst)
			continue ;
		cmd_expanded(cmd_lst, args);
		cmd_quote_clear(cmd_lst);
		args->env = from_lst_to_dbl(args->env_lst);
		pipex_main(cmd_lst, args);
		update_status(args);
	}
}

void	cmd_expanded(t_cmd_lst *cmd_lst, t_args *args)
{
	t_cmd	*cur;
	char	*str;

	cur = cmd_lst->head;
	str = NULL;
	while (cur)
	{
		str = expand(cur->args, args);
		free(cur->args);
		cur->args = str;
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
	return (arr);
}

void	update_status(t_args *a)
{
	t_env	*cur;

	cur = a->exp_lst->head->next;
	while (cur->next)
	{
		if (cur->data[11] == '?')
			remove_from_between(cur, a->exp_lst);
		cur = cur->next;
	}
	env_lst_add_last(a->exp_lst, ft_strjoin3("declare -x ?=\"",
		ft_itoa(g_status), "\""));
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
