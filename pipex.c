/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:04 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/06 15:48:12 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forking_separately(t_args *a, t_cmd *cur, int size)
{
	int	i;

	i = 0;
	a->size = size - 1;
	if (size == 1)
		forking(cur->fd_in, cur->fd_out, cur, a);
	else
	{
		forking(cur->fd_in, a->pipefds[0][1], cur, a);
		cur = cur->next;
		while (cur->next)
		{
			forking(a->pipefds[i][0], a->pipefds[i + 1][1], cur, a);
			if (i < size - 2)
				i++;
			cur = cur->next;
		}
		forking(a->pipefds[i][0], cur->fd_out, cur, a);
		i = -1;
		while (++i < size - 1)
		{
			close(a->pipefds[i][0]);
			close(a->pipefds[i][1]);
		}
	}
}

void	pipex_main(t_cmd_lst *cmd_lst, t_args *a)
{
	int		i;
	int		(*pipefds)[2];
	t_cmd	*cur;
	int		status;

	i = -1;
	cur = cmd_lst->head;
	if (!cur)
		ft_print_error_and_exit("nooooooooo\n", 1);
	pipefds = malloc(sizeof(*pipefds) * (cmd_lst->size - 1));
	while (++i < cmd_lst->size - 1)
		pipe_error(pipe(pipefds[i]));
	if (cmd_lst->size == 1)
		a->pipefds = NULL;
	else
		a->pipefds = pipefds;
	forking_separately(a, cur, cmd_lst->size);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cur = cmd_lst->head;
	closing(cur);
	i = -1;
	while (++i < cmd_lst->size)
		waitpid(-1, &status, 0);
}

void	forking(int pipefd_in, int pipefd_out, t_cmd *cur, t_args *a)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		ft_print_error_and_exit("fork failed\n", 1);
	if (child == 0)
	{
		sig_control(0);
		process(pipefd_in, pipefd_out, cur, a);
	}
}

void	process(int pipefd_in, int pipefd_out, t_cmd *cmd, t_args *a)
{
	int	i;
	int	b;

	i = -1;
	b = 0;
	dup_in_or_not_ttq(cmd, pipefd_in);
	dup_out_or_not_ttq(cmd, pipefd_out);
	while (a->pipefds && ++i < a->size)
	{
		close(a->pipefds[i][0]);
		close(a->pipefds[i][1]);
	}
	close_in_out(cmd->fd_out);
	close_in_out(cmd->fd_in);
	close_in_out(cmd->hdoc_fd);
	b = build(cmd, a);
	if (!b)
		execute(cmd, a->env);
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
	else
		ft_print_error_and_exit("execute() error\n", 1);
}
