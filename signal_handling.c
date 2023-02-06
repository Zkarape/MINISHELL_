/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:03:34 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/06 21:04:51 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	init_term()
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ECHOCTL;
	term.c_lflag |= ECHO;
	term.c_lflag &= ~ICANON;
	tcsetattr(0, 0, &term);
}

void	reset_term()
{
	struct termios term;

	tcgetattr(0, &term);
//	term.c_lflag &= ~ECHO;
	term.c_lflag |= ECHOCTL;
//	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	tcsetattr(0, 0, &term);
}
//The “mask” is a sigset_t, which is a set of signal numbers. The mask for signal sig expresses which signals the process can receive while it is handling signal number sig

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	ft_putchar_fd('\n', fd);
}

void	here_doc_sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	init_term();
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1, 0);
		ft_putstr_fd("\n", g_status, 0);
		rl_redisplay();
		close(g_status);
	}
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	init_term();
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1, 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		ft_putendl_fd("minishell: Quit 3", 2);
}

void	sig_int_nl(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_putendl_fd("", 1);
}
