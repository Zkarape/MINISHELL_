/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 22:17:56 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

int	heredoc(t_cmd *cmd, t_args *a)
{
	char	*tmp;
	char	*s;
	char	*cleaned_file;

	cleaned_file = filling_with_nulls(a->file);
	while (1)
	{
		sig_control(2);
		s = readline("> ");
		if (!s)
			break ;
		if (g_status == -42)
		{
			g_status = 1;
			free(cleaned_file);
			free(s);
			return (1);
		}
		if (!(ft_strncmp(cleaned_file, s, ft_strlen(s))
				!= 0 || s[0] == '\0'))
			break ;
		if (find_d_quotes(a->file, 0) == ft_strlen(a->file) - 1)
		{
			tmp = hdoc_expand(s, a);
			free(s);
			s = tmp;
		}
		if (cmd->yep && a->hdoc_size == 0)
		{
			ft_putstr_fd(s, a->fd[1], 1);
			cmd->hdoc_fd = a->fd[0];
		}
		free(s);
	}
	if (cmd->hdoc_fd == -1 && cmd->yep && a->hdoc_size == 0)
		cmd->hdoc_fd = a->fd[0];
	free(cleaned_file);
	free(s);
	return (0);
}

int	big_loop(t_cmd *cmd, t_args *a)
{
	t_red	*cur;
	int		fd[2];

	cur = cmd->red_lst->head;
	while (cur)
	{
		if (cur->type == HEREDOC)
		{
			if (pipe_error(pipe(fd)))
			{
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
			cmd->red_lst->heredoc_k--;
			a->hdoc_size = cmd->red_lst->heredoc_k;
			a->fd = fd;
			a->file = cur->file;
			if (heredoc(cmd, a))
				return (1);
			close(fd[1]);
			if (cmd->hdoc_fd == -1 && cmd->red_lst->heredoc_k == 0)
				close(fd[0]);
		}
		cur = cur->next;
	}
	return (0);
}
