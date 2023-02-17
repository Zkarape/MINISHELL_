#include "minishell.h"

void	init_term()
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ECHOCTL;
	term.c_lflag |= ECHO;
	tcsetattr(0, 0, &term);
}

void	reset_term()
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &term);
}

void	sig_control(int a)
{
	if (a == 0)
	{
		reset_term();
		signal(SIGINT, SIG_DFL);
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			perror("quited");
	//	ft_putstr_fd("\n", 1, 0);
	//	return (0);
	}
	else if (a == 1)
	{
		init_term();
		if (g_status == -5)
			signal(SIGINT, SIG_IGN);
		else	
			signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	//	return (1);
	}
	else if (a == 2)
	{
		signal(SIGINT, SIG_DFL);	
		signal(SIGQUIT, SIG_IGN);
	//	return (2);
	}
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_handler_hdoc(int sig)
{
	if (sig == SIGINT)
	{
		g_status = -42;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
