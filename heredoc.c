/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/21 21:29:25 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

int	heredoc(t_red *red_node, t_env_lst *env_lst, t_cmd *cmd, int yep)
{
	int		i;
	int		tmp_fd = 0;
	char	*s;
	char	*cleaned_file;

	i = -1;
	s = readline("> ");
	cleaned_file = filling_with_nulls(red_node->file);
	tmp_fd = open("/Users/zkarapet/Desktop/MINISHELL_/k5",
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (ft_strncmp(cleaned_file, s, ft_strlen(s)) != 0 || s[0] == '\0')
	{
		if (find_d_quotes(red_node->file, 0) == ft_strlen(red_node->file) - 1)
			s = hdoc_expand(s, env_lst);
		printf("yeep == %d\n", yep);
		if (yep)
			ft_putstr_fd(s, tmp_fd, 1);
		s = readline("> ");
	}
	close(tmp_fd);
	//signal for ^C
	return (tmp_fd);
}

int	big_loop(t_cmd *cmd, t_env_lst *env_lst, int yep)
{
	t_red	*cur;
	int		tmp_fd;

	tmp_fd = -1;
	cur = cmd->red_lst->head;
	while (cur)
	{
		if (cur->type == HEREDOC)
		{
			cmd->red_lst->heredoc_k--;
			tmp_fd = heredoc(cur, env_lst, cmd, yep);
		}
		cur = cur->next;
	}
	return (tmp_fd);
}
