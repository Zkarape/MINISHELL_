/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:30:41 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/18 15:42:52 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
}

int	pipe_error(int pip)
{
	if (pip < 0)
	{
		perror("pipe() returns -1\n");
		return (1);
	}
	return (0);
}

void	ft_print_error_and_exit(char *error, int code)
{
	ft_putstr(error);
	g_status = code;
	exit(code);
}

void	dup_error(int du)
{
	if (du < 0)
		ft_print_error_and_exit("dup2 is < 0", 1);
}

void	ft_print_error_with_arg(char *cmd, char *arg)
{
	char	*msg;
	char	*s1;
	char	*s2;

	s1 = ft_strjoin_m(cmd, ": ");
	s2 = ft_strjoin_m(arg, ": ");
	msg = ft_strjoin3(s1, s2, "No such file or directory\n");
	ft_putstr(msg);
}

int	parsing_error_checks(char *s)
{
//	if (s[0] == '\n')
//	{
//		g_status = 1;
//		return (1);
//	}
	if (!find_unquoted(s))
	{
		ft_putstr_fd("Missing quote\n", 1, 0);
		g_status = 1;
		return (1);
	}
	else if (!last_pipe_check(s))
	{
		ft_putstr_fd("Parsing error near '|'\n", 1, 0);
		g_status = 1;
		return (1);
	}
	g_status = 0;
	return (0);
}
