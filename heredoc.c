/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/02 21:49:41 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	heredoc(t_cmd *cmd, int yep, t_args *a)
{
	char	*tmp;
	char	*s;
	char	*cleaned_file;

	s = readline("> ");
	cleaned_file = filling_with_nulls(a->file);
	while (ft_strncmp(cleaned_file, s, ft_strlen(s)) != 0 || s[0] == '\0')
	{
		if (find_d_quotes(a->file, 0) == ft_strlen(a->file) - 1)
		{
			tmp = hdoc_expand(s, a);
			free(s);
			s = tmp;
		}
		if (yep && a->hdoc_size == 0)
		{
			ft_putstr_fd(s, a->fd[1], 1);
			cmd->hdoc_fd = a->fd[0];
		}
		sig_handle(3);
		s = readline("> ");
	}
	if (cmd->hdoc_fd == -1 && yep && a->hdoc_size == 0)
		cmd->hdoc_fd = a->fd[0];
}

void	big_loop(t_cmd *cmd, int yep, t_args *a)
{
	t_red	*cur;
	int		fd[2];

	cur = cmd->red_lst->head;
	while (cur)
	{
		if (cur->type == HEREDOC)
		{
			pipe_error(pipe(fd));
			cmd->red_lst->heredoc_k--;
			a->hdoc_size = cmd->red_lst->heredoc_k;
			a->fd = fd;
			a->file = cur->file;
			heredoc(cmd, yep, a);
			close(fd[1]);
			if (cmd->hdoc_fd == -1 && cmd->red_lst->heredoc_k == 0)
				close(fd[0]);
		}
		cur = cur->next;
	}
}
