/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:06:24 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/15 21:30:22 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	until_equal_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

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
		printf("s2 == %s\n", cmd_node->no_cmd[i]);
		ft_putstr_fd(cmd_node->no_cmd[i], cmd_node->fd_out, 0);
		i++;
		if (cmd_node->no_cmd[i])
			ft_putstr_fd(" ", cmd_node->fd_out, 0);
	}
	if (k)
		ft_putstr_fd("\n", cmd_node->fd_out, 0);
}

int	error_checks_for_var(char *s, int until)
{
	int	i;

	i = 0;
	if (!s || s[0] == '_')
		return (0);
	if (!is_alpha(s[0]))
	{
		ft_putstr(s);
		ft_print_error_and_exit(": not a valid identifier\n", 1);
	}
	while (s[i] && i < until)
	{
		if (!is_num(s[i]) && s[i] != '_' && !is_alpha(s[i]))
		{
			ft_putstr(s);
			ft_print_error_and_exit(": not a valid identifier\n", 1);
		}
		i++;
	}
	return (1);
}

void	unset(t_env_lst *env_lst, t_cmd *cmd_node)
{
	int		i;
	int		j;
	t_env	*env_node;

	i = 0;
	j = -1;
	env_node = env_lst->head->next;
	while (cmd_node->no_cmd[++i])
	{
		error_checks_for_var(cmd_node->no_cmd[i], ft_strlen(cmd_node->no_cmd[i]));
		while (env_node->next)
		{
			if (!ft_strncmp(env_node->data, cmd_node->no_cmd[i],
					until_equal_sign(env_node->data)))
			{
				remove_from_between(env_node, env_lst);
			}
			env_node = env_node->next;
		}
	}
}

void	env(t_env_lst *env_lst)
{
	env_lst_print(env_lst);
}

void	pwd()
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
	else
		perror("pwd error\n");
}
