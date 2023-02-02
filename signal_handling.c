/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:03:34 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/02 21:58:49 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ECHOCTL;
	term.c_lflag |= ECHO;
	tcsetattr(0, 0, &term);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1, 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	print(int sig)
{
	printf("signal interrupted\n");
}

void	sig_handler_for_hdoc(int sig)
{
	struct termios	old_term;
	struct termios	new_term;

	tcgetattr(0, &new_term);
	old_term = new_term;
	new_term.c_lflag &= ~ICANON;
	//to deny canonical mode, especially not to read line by line and end prompt with enter
//	sigint_handler(sig);
	tcsetattr(0, 0, &new_term);
	print(sig);
//	sigint_handler(sig);
	tcsetattr(0, 0, &old_term);
}

void	sig_handle(int a)
{
	if (a == 1)//main
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (a == 2)//child
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (a == 3)//heredoc
	{
	//	signal(SIGINT, SIG_DFL);
		signal(SIGINT, sig_handler_for_hdoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
