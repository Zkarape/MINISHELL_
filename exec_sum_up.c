/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sum_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:03:48 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/18 15:02:05 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_input_work(t_red_lst *red_lst)
{
	t_red	*cur;
	int		i;

	i = 0;
	cur = red_lst->head;
	while (cur)
	{
		if (cur->type == HEREDOC)
			i = 1;
		else if (cur->type == INPUT_REDIRECTION)
			i = 0;
		cur = cur->next;
	}
	return (i);
}

void	dup_or_not_ttq(t_cmd_lst *cmd_lst, int *pipefd)
{
	t_cmd	*cur;

	cur = cmd_lst->head;
	if (!cur)
		return ;
	while (cur)
	{
		if (cur->fd_in != 0)
			dup2(cur->fd_in, pipefd[0]);
		if (cur->fd_out != 1)
			dup2(cur->fd_out, pipefd[1]);
		cur = cur->next;
	}
}
