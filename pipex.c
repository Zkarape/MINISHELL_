/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:04 by aivanyan          #+#    #+#             */
/*   Updated: 2023/01/18 15:01:48 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**g_envp;

void	pipex_main(t_env_lst *env_lst, t_env_lst *exp_lst)
{	
	int		pipefd[2];

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

void	process(int *pipefd, char **env, int is_first, t_cmd *cmd)
{
	if (is_first)
	{
		close(pipefd[0]);
		if (dup2(fd, cmd->fd_in) < 0 || dup2(pipefd[1], cmd->fd_out) < 0)
			ft_exit();
		close(fd);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], cmd->fd_in) < 0 || dup2(fd, cmd->fd_out) < 0)
			ft_exit();
		close(fd);
	}
	execute(cmd->no_cmd[0], env);
}

void	execute(char *cmd, char **env)
{
	char	**args;
	char	*paths;
	char	**path;
	char	*absolue_path;
	int		i;

	i = 0;
	absolue_path = NULL;
	args = ft_split(cmd, ' ');
	execve(args[0], args, env);
	paths = get_environment("PATH=");
	path = ft_split(paths, ':');
	if (path)
	{
		while (path[i])
		{
			absolue_path = ft_strjoin3(path[i++], "/", args[0]);
			execve(absolue_path, args, env);
			free(absolue_path);
		}
	}
	ft_exit();
}
