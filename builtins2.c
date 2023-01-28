/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:05:06 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/27 13:39:32 by aivanyan         ###   ########.fr       */
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

void	cd(char *path)
{
	if (chdir(path))
		ft_print_error_and_exit("No such file or directory", 1);
}
