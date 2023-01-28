/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/27 19:32:14 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char **env_)
{
	char		*s;
	t_list		*lst;
	t_env_lst	*env_lst;
	t_cmd_lst	*cmd_lst;
	t_env_lst	*exp_lst;

	s = NULL;
	env_lst = getting_env(env_);
	exp_lst = exp_cpy_env(env_lst);
	while (1)
	{
		s = readline("minishell$ ");
		add_history(s);
		lst = group_until_pipe(s);
		cmd_lst = grouping_with_red(lst, env_lst);
		cmd_expanded(cmd_lst, exp_lst);
		cmd_quote_clear(cmd_lst);
		pipex_main(cmd_lst,  env_);
		//		cmd_lst_print(cmd_lst);
		//		unset(env_lst, cmd_lst->head);
		//		ft_export(cmd_lst->head, env_lst, exp_lst);
		//		echo(cmd_lst->head);
		//		env(exp_lst);
		//		env_lst_print(env_lst);
	}
}

void	cmd_expanded(t_cmd_lst *cmd_lst, t_env_lst *exp_lst)
{
	t_cmd	*cur;
	char	*str;

	cur = cmd_lst->head;
	str = NULL;
	while (cur)
	{
		str = expand(cur->args, exp_lst);
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
		cur->no_cmd = no_cmd_clear(arr);
	//	printf("s == %s\n", cur->no_cmd[1]);
		cur = cur->next;
	}
}
