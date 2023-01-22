/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:04 by aivanyan          #+#    #+#             */
/*   Updated: 2023/01/22 21:56:38 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	closing(int (*pipefds)[2], int size)
//{
//	int	i;
//
//	i = -1;
//}
//
void	pipe_error(int pip)
{
	if (pip < 0)
		perror("pipe() returns -1\n");
}

void	pipex_main(t_cmd_lst *cmd_lst, char **env)
{
	int		i;
	int		(*pipefds)[2];
	t_cmd	*cur;
	int		status;

	i = -1;
	cur = cmd_lst->head;
	if (!cur)
		ft_print_error_and_exit("nooooooooo\n", 1);
	if (cmd_lst->size == 1)
		forking(cur->fd_in, cur->fd_out, 12657, 1, env, cur, NULL);
	else
	{
		pipefds = malloc(sizeof(*pipefds) * (cmd_lst->size - 1));
		while (++i < cmd_lst->size - 1)
		{
			pipe_error(pipe(pipefds[i]));
		}
		i = 0;
		forking(cur->fd_in, pipefds[0][1], 0, cmd_lst->size - 1, env, cur, pipefds);
		cur = cur->next;
		while (cur->next)
		{
			forking(pipefds[i][0], pipefds[i + 1][1], i + 1, cmd_lst->size - 1, env, cur, pipefds);
			if (i < cmd_lst->size - 2)
				i++;
			cur = cur->next;
		}
		printf("i == %d\n", i);
		forking(pipefds[i][0], cur->fd_out, i, cmd_lst->size - 1, env, cur, pipefds);
		i = -1;
		while (++i < cmd_lst->size - 1)
		{
			close(pipefds[i][0]);
			close(pipefds[i][1]);
		}
	}
	i = -1;
	while (++i < cmd_lst->size)
		waitpid(-1, &status, 0);
}

void	forking(int pipefd_in, int pipefd_out, int i, int size, char **env, t_cmd *cur, int (*pipefds)[2])
{
	pid_t	child;

	child = fork();
	if (child < 0)
		ft_print_error_and_exit("fork failed\n", 1);
	if (child == 0)
		process(pipefd_in, pipefd_out, env, i, size, cur, pipefds);
}

void	process(int pipefd_in, int pipefd_out, char **env, int i, int size, t_cmd *cmd, int (*pipefds)[2])
{
	if (i != 0)
		dup_in_or_not_ttq(cmd, pipefd_in);
	if (i != size)
		dup_out_or_not_ttq(cmd, pipefd_out);
	i = -1;
	while (pipefds && ++i < size)
	{
		close(pipefds[i][0]);
		close(pipefds[i][1]);
	}
	close(cmd->fd_out);
	close(cmd->fd_in);
	execute(cmd, env);
}

void	execute(t_cmd *cmd, char **env)
{
	char	*paths;
	char	**path;
	char	*absolue_path;
	int		i;

	i = 0;
	absolue_path = NULL;
	execve(cmd->no_cmd[0], cmd->no_cmd, env);
	paths = get_environment("PATH=", env);
	path = split(paths, ':');
	if (path)
	{
		while (path[i])
		{
			absolue_path = ft_strjoin3(path[i++], "/", cmd->no_cmd[0]);
			execve(absolue_path, cmd->no_cmd, env);
			free(absolue_path);
		}
	}
	ft_print_error_and_exit("execute() error\n", 1);
}
