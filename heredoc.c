/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/12 18:16:28 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	

int	heredoc(t_red *red_node, t_env_lst *env_lst)
{
	int		i;
	int		tmp_fd;
	char	*s;
	char	*cleaned_file;

	i = -1;
	s = readline("> ");
	cleaned_file = filling_with_nulls(red_node->file);
	tmp_fd = open("/Users/zkarapet/Desktop/MINISHELL_2/k5",
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("nooot openedd:: ");
	while (ft_strncmp(cleaned_file, s, ft_strlen(s)) != 0 || s[0] == '\0')
	{
		if (find_d_quotes(red_node->file, 0) == ft_strlen(red_node->file) - 1)
			s = hdoc_expand(s, env_lst);
//		printf("s == %s\n", s);
		ft_putstr_fd(s, tmp_fd);
		s = readline("> ");
//		printf("retval == %d\n", find_d_quotes(red_node->file, 0));
	}
//	printf("helllooooooooy\n");
	//signal for ^C
	return (tmp_fd);
}

void	big_loop(t_cmd *cmd, t_env_lst *env_lst)
{
	int		tmp_fd;
	t_red	*cur;

	cur = cmd->red_lst->head;
	while (cur)
	{
		if (cur->type == 2)
		{
			cmd->red_lst->heredoc_k--;
			tmp_fd = heredoc(cur, env_lst);
			if (cmd->red_lst->heredoc_k > 0)
				close(tmp_fd);
		}
		cur = cur->next;
	}
	cmd->fd_in = tmp_fd;
}
