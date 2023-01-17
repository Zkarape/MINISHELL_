/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:04 by aivanyan          #+#    #+#             */
/*   Updated: 2022/10/29 19:57:43 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		filefd[2];

	g_envp = envp;
	if (argc != 5)
	{
		write(STDOUT_FILENO, "Invalid number of arguments\n", 28);
		return (EXIT_FAILURE);
	}
	filefd[0] = open(argv[1], O_RDONLY);
	filefd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (filefd[0] < 0 || filefd[1] < 0)
		ft_exit();
	if (pipe(pipefd) < 0)
		ft_exit();
	forking(pipefd, filefd, argv);
	wait(NULL);
	wait(NULL);
}

void	forking(int *pipefd, int *filefd, char **argv)
{
	int		i;
	pid_t	child;

	i = 0;
	while (i < 2)
	{
		child = fork();
		if (child < 0)
			ft_exit();
		if (child == 0)
			process(pipefd, filefd[i], argv[i + 2], 1 - i);
		close(pipefd[1 - i++]);
	}
}

void	process(int *pipefd, int fd, char *cmd, int is_first)
{
	if (is_first)
	{
		close(pipefd[0]);
		if (dup2(fd, STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
			ft_exit();
		close(fd);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(fd, STDOUT_FILENO) < 0)
			ft_exit();
		close(fd);
	}
	execute(cmd);
}

void	execute(char *cmd)
{
	char	**args;
	char	*paths;
	char	**path;
	char	*absolue_path;
	int		i;

	i = 0;
	absolue_path = NULL;
	args = ft_split(cmd, ' ');
	execve(args[0], args, g_envp);
	paths = get_environment("PATH=");
	path = ft_split(paths, ':');
	if (path)
	{
		while (path[i])
		{
			absolue_path = ft_strjoin3(path[i++], "/", args[0]);
			execve(absolue_path, args, g_envp);
			free(absolue_path);
		}	
	}
	ft_exit();
}
