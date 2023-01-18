/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 21:39:09 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/18 14:04:00 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_cmd *cmd, t_env_lst *env_lst, t_env_lst *exp_lst)
{
	int		i;
	char	*val;
	t_env	*exp_cur;
	t_env	*env_cur;

	i = 0;
	val = NULL;
	while (cmd->no_cmd[++i])
	{
		val = equality_out_of_quotes(cmd->no_cmd[i]);
		exp_cur = is_in_export_or_not(exp_lst, cmd->no_cmd[i]);
		remove_from_between(exp_cur, exp_lst);
		export_pars(cmd->no_cmd[i], exp_lst);
		if (val)
		{
			env_cur = is_in_env_or_not(env_lst, cmd->no_cmd[i]);
			remove_from_between(env_cur, env_lst);
			env_lst_add_last(env_lst, cmd->no_cmd[i]);
		}
	}
	sort(exp_lst);
//	env(exp_lst);
}

void	export_pars(char *s, t_env_lst *exp_lst)
{
	int			i;
	char		*data;
	char		*unquoted;
	char		*quoted;

	i = 0;
	data = NULL;
	unquoted = equality_out_of_quotes(s);
	quoted = adding_quotes(unquoted);
	data = ft_strjoin(s, quoted, ft_strlen(quoted),
		0, ft_strlen(s) - ft_strlen(unquoted));
	env_lst_add_last(exp_lst, ft_strjoin("declare -x ", data, ft_strlen(data), 0, 11));
}

t_env_lst	*exp_cpy_env(t_env_lst *env_lst)
{
	t_env		*cur;
	t_env_lst	*exp_lst;

	cur = env_lst->head->next;
	exp_lst = env_lst_construct();
	while (cur->next)
	{
		export_pars(cur->data, exp_lst);
		cur = cur->next;
	}
	return (exp_lst);
}
