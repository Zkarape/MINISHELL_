/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:05:06 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/29 15:38:57 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	env(t_env_lst *env_lst, char *arg, char **envv)
{
	if (!get_environment("PATH=", envv))
		ft_print_error_and_exit("env: No such file or directory\n", 1);
	if (arg)
		ft_print_error_with_arg("env", arg, 1);
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

void	cd(char *path, char **env)
{
	if (!path)
	{
		if (chdir(get_environment("HOME=", env)))
			ft_print_error_with_arg("cd", path, 1);
	}
	else
	{
		if (chdir(path))
			ft_print_error_with_arg("cd", path, 1);
	}
}
