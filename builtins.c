/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:06:24 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/16 17:45:27 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	until_equal_sign(char *s)
{
	int	i;

	i = 0;
//	printf("****s**** ==  %s\n", s);
	while (s && s[i] && s[i] != '=')
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

void	remove_cur_env_node(t_env_lst *env_lst, char *s)
{
	t_env	*cur;

	cur = env_lst->head->next;
	while (cur->next)
	{
		if (!ft_strncmp(cur->data, s, until_equal_sign(cur->data) + 1))
			remove_from_between(cur, env_lst);
		cur = cur->next;
	}
}

void	unset(t_env_lst *env_lst, t_env_lst *exp_lst, t_cmd *cmd_node)
{
	int		i;
	int		j;
	int		k;
	t_env	*exp_node;

	i = 0;
	j = -1;
	exp_node = exp_lst->head->next;
	while (cmd_node->no_cmd[++i])
	{
		error_checks_for_var(cmd_node->no_cmd[i], ft_strlen(cmd_node->no_cmd[i]));
		while (exp_node->next)
		{
			k = until_equal_sign(&exp_node->data[11]);
			if (!ft_strncmp(&exp_node->data[11], cmd_node->no_cmd[i], k)
				&& k == ft_strlen(cmd_node->no_cmd[i]))
			{
				remove_cur_env_node(env_lst, &exp_node->data[11]);
				remove_from_between(exp_node, exp_lst);
			}
			exp_node = exp_node->next;
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
