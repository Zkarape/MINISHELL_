/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/14 20:48:46 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char **env_)
{
	char		*s;
	int i = 1;
	t_list		*lst;
	t_env_lst	*env_lst;
	t_cmd_lst	*cmd_lst;
	t_env_lst	*exp_lst;	

	s = NULL;
	env_lst = getting_env(env_);
	exp_lst = exp_cpy_env(env_lst);
	while (i-- > 0)
	{
		s = readline("minishell$ ");
		lst = group_until_pipe(s);
		cmd_lst = grouping_with_red(lst, env_lst);
		cmd_expanded(cmd_lst, exp_lst);
		printf("data == %s\n", cmd_lst->head->args);
		cmd_quote_clear(cmd_lst);
		cmd_lst_print(cmd_lst);
//		unset(env_lst, cmd_lst->head);
//		ft_export(cmd_lst->head, env_lst, exp_lst);
		echo(cmd_lst->head);
		//env(exp_lst);
//		env_lst_print(env_lst);
		//cmd_lst_print(cmd_lst);
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
		str = cur->args;
		free(cur->args);
		cur->args = expand(str, exp_lst);
		cur = cur->next;
	}
}

void	print(char **spl)
{
	for (int i = 0; i < 3; i++)
	{
		printf("spl == %s\n", spl[i]);
	}
}

void	cmd_quote_clear(t_cmd_lst *cmd_lst)
{
	t_cmd	*cur;
	char	*str;

	cur = cmd_lst->head;
	str = NULL;
	while (cur)
	{
		str = filling_with_nulls(cur->args);
		cur->no_cmd = split(str);
		print(cur->no_cmd);
		cur = cur->next;
	}
}
