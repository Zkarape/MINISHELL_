#include "minishell.h"

void	disable_canonical_mode(t_args a)
{
	tcgetattr(0, &a.term);
	a.term.c_lflag &= ~(ECHOCTL);
	a.term.c_lflag &= ~(ICANON);
	tcgetattr(0, &a.term);
}

void	enable_canonical_mode(t_args a)
{
	tcgetattr(0, &a.term);
	a.term.c_lflag |= (ECHOCTL);
	a.term.c_lflag |= (ICANON);
	tcgetattr(0, &a.term);
}
