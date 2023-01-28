/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/27 15:56:08 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	heredoc(t_red *red_node, t_env_lst *env_lst, t_cmd *cmd, int yep, int *fd, int hdoc_size)
{
	char	*tmp;
	int		i;
	char	*s;
	char	*cleaned_file;

	i = -1;
	s = readline("> ");
	cleaned_file = filling_with_nulls(red_node->file);
	while (ft_strncmp(cleaned_file, s, ft_strlen(s)) != 0 || s[0] == '\0')
	{
		if (find_d_quotes(red_node->file, 0) == ft_strlen(red_node->file) - 1)
		{
			tmp = hdoc_expand(s, env_lst);
			free(s);
			s = tmp;
		}
		if (yep && hdoc_size == 0)
		{
			ft_putstr_fd(s, fd[1], 1);
			cmd->hdoc_fd = fd[0];
		}
		s = readline("> ");
	}
	if (cmd->hdoc_fd == -1 && yep && hdoc_size == 0)
	{
			ft_putstr_fd("\0", fd[1], 0);
			cmd->hdoc_fd = fd[0];
	}
	//signal for ^C
}

void	big_loop(t_cmd *cmd, t_env_lst *env_lst, int yep)
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
			heredoc(cur, env_lst, cmd, yep, fd, cmd->red_lst->heredoc_k);
			close(fd[1]);
			if (cmd->hdoc_fd == -1 && cmd->red_lst->heredoc_k == 0)
				close(fd[0]);
		}
		cur = cur->next;
	}
}
