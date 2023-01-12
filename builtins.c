/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:06:24 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/12 21:57:39 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_cmd *cmd_node)
{
	int	i;
	int	k;
	
	i = 1;
	k = 1;
	if (ft_strncmp(cmd_node->no_cmd[1], "-n", 2) == 0)
	{
		i++;
		k = 0;
	}
	while (cmd_node->no_cmd[i])
	{
		ft_putstr_fd(cmd_node->no_cmd[i], cmd_node->fd_out, 0);
		i++;
		if (cmd_node->no_cmd[i])
			ft_putstr_fd(" ", cmd_node->fd_out, 0);
	}
	if (k)
		ft_putstr_fd("\n", cmd_node->fd_out, 0);
}

void	unset(t_env_lst *env_lst, t_cmd *cmd_node)
{
	int	i;

	i = -1;
	while (cmd_node->no_cmd[++i])
	{
		
	}
}
