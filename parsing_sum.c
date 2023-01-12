/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/12 18:27:13 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char **env)
{
	int			i;
	char		*s;
	t_list		*lst;
	t_env_lst	*env_lst;
	t_cmd_lst	*cmd_lst;

	s = NULL;
	env_lst = getting_env(env);
	while (1)
	{
		s = readline("minishell$ ");
		lst = group_until_pipe(s);
		cmd_lst = grouping_with_red(lst, env_lst);
		cmd_expanded(cmd_lst, env_lst);
		cmd_quote_clear(cmd_lst);
		cmd_lst_print(cmd_lst);
	}
}

void	cmd_expanded(t_cmd_lst *cmd_lst, t_env_lst *env_lst)
{
	t_cmd	*cur;

	cur = cmd_lst->head;
	while (cur)
	{
		cur->args = expand(cur->args, env_lst);
		cur = cur->next;
	}
}

void	cmd_quote_clear(t_cmd_lst *cmd_lst)
{
	t_cmd	*cur;

	cur = cmd_lst->head;
	while (cur)
	{
		cur->args = filling_with_nulls(cur->args);
		cur = cur->next;
	}
}
