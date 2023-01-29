/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:56:46 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/29 15:48:09 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_routine(t_env_lst *env_lst, t_env_lst *exp_lst, t_cmd *cmd, char **envv)
{
	int		i;
	char	*low;

	i = 1;
	low = ft_str_tolower(cmd->no_cmd[0]);
	if (i)
	{
		if (!ft_strncmp(cmd->no_cmd[0], "exit", 5))
			ft_exit(cmd);
		else if (!ft_strncmp(low, "env", 4))
			env(env_lst, cmd->no_cmd[1], envv);
		else if (!ft_strncmp(low, "pwd", 4))
			pwd();
		else if (!ft_strncmp(cmd->no_cmd[0], "cd", 3))
			cd(cmd->no_cmd[1], envv);
		else if (!ft_strncmp(low, "echo", 5))
		{
		//	printf("helllo\n");
			echo(cmd);
		}
		else if (!ft_strncmp(cmd->no_cmd[0], "unset", 6))
			unset(env_lst, exp_lst, cmd);
		else if (!ft_strncmp(cmd->no_cmd[0], "export", 7))
			ft_export(cmd, env_lst, exp_lst);
		else
			i = 0;
	}
	free(low);
	return (i);
}
