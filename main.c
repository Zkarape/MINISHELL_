#include "minishell.h"

int	main(int ac, char **av, char **env)
{
//	int fd1 = open("oko", O_WRONLY | O_APPEND | O_CREAT, 0644);
//	printf("fd == %d\n", fd1);
//	int fd2 = open("l", O_WRONLY | O_APPEND | O_CREAT, 0644);
//	printf("fd == %d\n", fd2);
	parsing(env);
}
