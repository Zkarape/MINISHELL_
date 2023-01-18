/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/18 14:42:11 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	

void	heredoc(t_red *red_node, t_env_lst *env_lst, t_cmd *cmd, int yep)
{
	int		i;
	int		tmp_fd;
	char	*s;
	char	*cleaned_file;

	i = -1;
	s = readline("> ");
	cleaned_file = filling_with_nulls(red_node->file);
	tmp_fd = open("/Users/zkarapet/Desktop/MINISHELL_/k5",
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("nooot openedd:: ");
	while (ft_strncmp(cleaned_file, s, ft_strlen(s)) != 0 || s[0] == '\0')
	{
		if (find_d_quotes(red_node->file, 0) == ft_strlen(red_node->file) - 1)
			s = hdoc_expand(s, env_lst);
		ft_putstr_fd(s, tmp_fd, 1);
		s = readline("> ");
	}
	//signal for ^C
	if (yep)
		dup2(tmp_fd, cmd->fd_in);
}

void	big_loop(t_cmd *cmd, t_env_lst *env_lst, int yep)
{
	int		tmp_fd;
	t_red	*cur;

	cur = cmd->red_lst->head;
	while (cur)
	{
		if (cur->type == 2)
		{
			cmd->red_lst->heredoc_k--;
			tmp_fd = heredoc(cur, env_lst, cmd, yep);
			if (cmd->red_lst->heredoc_k > 0)
				close(tmp_fd);
		}
		cur = cur->next;
	}
	cmd->fd_in = tmp_fd;
}
