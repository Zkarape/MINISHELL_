/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:56:51 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/15 22:57:17 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char *var_name, char *cwd, t_args *a)
{
	char	*str;
	t_env	*cur;

	str = ft_strjoin_m(var_name, cwd);
	free(cwd);//current working directory
	cur = is_in_env_or_not(a->env_lst, str);
	if (cur)
	{
		remove_from_between(cur, a->env_lst);
		remove_from_between(cur, a->exp_lst);
		export_pars(str, a);
		env_lst_add_last(a->env_lst, str);
	}
	if (ft_strncmp("OLDPWD=", var_name, 7))
	{
		export_pars(str, a);
		if (cwd)
			env_lst_add_last(a->env_lst, str);
	}
	free(str);
}

int	cd(char *path, char **env, t_args *a)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!path)
	{
		if (chdir(get_environment("HOME=", env)))
			ft_print_error_with_arg("cd", path, 1);
	}
	else
	{
		change_pwd("OLDPWD=", cwd, a);
		cwd = getcwd(NULL, 0);
		change_pwd("PWD=", cwd, a);
		if (chdir(path))
			ft_print_error_with_arg("cd", path, 1);
	}
	return (0);
}
