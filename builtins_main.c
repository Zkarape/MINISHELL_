/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:56:46 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/20 14:14:02 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_routine(t_env_lst *env_lst, t_env_lst *exp_lst, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->no_cmd[0], "exit", 5))
		ft_exit(cmd);
	else if (!ft_strncmp(cmd->no_cmd[0], "env", 4))
		env(env_lst);
	else if (!ft_strncmp(cmd->no_cmd[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(cmd->no_cmd[0], "cd", 3))
		cd(cmd->no_cmd[1]);
	else if (!ft_strncmp(cmd->no_cmd[0], "echo", 5))
		echo(cmd);
	else if (!ft_strncmp(cmd->no_cmd[0], "unset", 6))
		unset(env_lst, exp_lst, cmd);
	else if (!ft_strncmp(cmd->no_cmd[0], "export", 7))
		ft_export(cmd, env_lst, exp_lst);
}
