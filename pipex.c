/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:04 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/18 19:04:20 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void checking_fork(t_args *a, pid_t forking, int i)
{
	// static int	i = 0;
	int j;

	j = -1;
	a->pids[i + 1] = forking;
	if (forking < 0)
	{
		while (a->pids[++j] != a->pids[i + 1])
			kill(a->pids[j], 0);
	}
}
// A process terminates normally when its program signals it is done by calling exit. Returning from main is equivalent to calling exit, and the value that main returns is used as the argument to exit. WIFEXITED(status) checks if child terminated normally, WEXITSTATUS(status) generates exit status of child, WTERMSIG(status) macro returns the numeric value of the signal that was raised by the child process

void processing_status(t_args *a, int size)
{
	pid_t pid;
	int i;
	int status;

	i = -1;
	while (++i < size)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == a->pids[size - 1])
		{
			if (!WTERMSIG(status)) // child completed successfully
				g_status = WEXITSTATUS(status);
			else // terminated with failure
			{
				g_status = WTERMSIG(status) + 128;
				if (g_status == 130)
					write(1, "\n", 1);
				else if (g_status == 131)
					ft_putstr_fd("Quit 3", 1, 1);
			}
		}
	}
}

void forking_separately(t_args *a, t_cmd *cur, int size)
{
	int i;
	int j;
	int b;

	i = 0;
	j = 0;
	b = 0;
	a->size = size - 1;
	a->pids = malloc(sizeof(pid_t) * (size));
	if (size == 1)
		checking_fork(a, forking(cur->fd_in, cur->fd_out, cur, a), i - 1);
	else
	{
		checking_fork(a, forking(cur->fd_in, a->pipefds[0][1], cur, a), i - 1);
		cur = cur->next;
		while (cur->next)
		{
			checking_fork(a, forking(a->pipefds[i][0], a->pipefds[i + 1][1], cur, a), i);
			if (i < size - 2)
				i++;
			cur = cur->next;
		}
		checking_fork(a, forking(a->pipefds[i][0], cur->fd_out, cur, a), i);
		close_pipefds(a->pipefds, size - 1, NULL, 0);
	}
}

int pipex_main(t_cmd_lst *cmd_lst, t_args *a)
{
	int i;
	int(*pipefds)[2];
	t_cmd *cur;

	i = -1;
	cur = cmd_lst->head;
	a->cmd_lst_size = cmd_lst->size;
	if (!cur)
		return (1);
	pipefds = malloc(sizeof(int *) * (cmd_lst->size - 1));
	while (++i < cmd_lst->size - 1)
	{
		if (pipe_error(pipe(pipefds[i])))
		{
			close_pipefds(pipefds, i, cur, 1);
			//			pipefds_free(pipefds, cmd_lst->size - 1);
			return (1);
		}
	}
	if (cmd_lst->size == 1)
		a->pipefds = NULL;
	else
		a->pipefds = pipefds;
	forking_separately(a, cur, cmd_lst->size);
	cur = cmd_lst->head;
	closing(cur);
	processing_status(a, cmd_lst->size);
	//	pipefds_free(pipefds, cmd_lst->size - 1);
	return (0);
}

pid_t forking(int pipefd_in, int pipefd_out, t_cmd *cur, t_args *a)
{
	pid_t pid;
	int i;

	i = -1;
	pid = fork();
	if (pid == 0)
	{
		
		sig_control(0);
		process(pipefd_in, pipefd_out, cur, a);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (pid);
}

void process(int pipefd_in, int pipefd_out, t_cmd *cmd, t_args *a)
{
	int i;
	int b;

	i = -1;
	b = 0;
	if (red_big_loop(cmd))
		ft_print_error_and_exit("file not found\n", 127);
	dup_in_or_not_ttq(cmd, pipefd_in);
	// printf("00000000011111 ========== %s\n", cmd->no_cmd[0]);
	// printf("11111111122222 ========== %s\n", cmd->no_cmd[1]);
	dup_out_or_not_ttq(cmd, pipefd_out);
	printf("000000000 ========== %s\n", cmd->no_cmd[0]);
	printf("111111111 ========== %s\n", cmd->no_cmd[1]);
	while (a->pipefds && ++i < a->size)
	{
		close(a->pipefds[i][0]);
		close(a->pipefds[i][1]);
	}
	close_in_out(cmd->fd_out);
	close_in_out(cmd->fd_in);
	close_in_out(cmd->hdoc_fd);
	if (!cmd->no_cmd[0])
		exit(1);

	b = build(cmd, a);
	if (!b)
	{
		execute(cmd, a->env);
	}
	else
	{
		printf("exited\n");
		exit(g_status);
	}
}

void execute(t_cmd *cmd, char **env)
{
	char *paths;
	char **path;
	char *absolue_path;
	int i;

	i = 0;
	absolue_path = NULL;
	printer(cmd->no_cmd);

	//	if (execve(cmd->no_cmd[0], cmd->no_cmd, env) == -1)
	//		perror(cmd->no_cmd[0]);
	paths = get_environment("PATH=", env);
	path = split(paths, ':');
	if (path)
	{
		while (path[i])
		{
			absolue_path = ft_strjoin3(path[i++], "/", cmd->no_cmd[0]);
			//	printf("absolute path before%s\n", absolue_path);
			execve(absolue_path, cmd->no_cmd, env);
			//		perror(cmd->no_cmd[0]);
			//	printf("absolute path after%s\n", absolue_path);
			free(absolue_path);
		}
	}
	ft_print_error_and_exit("cmd not found\n", 127);
}
