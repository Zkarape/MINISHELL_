/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:17:00 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/25 01:06:38 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char c)
{
	return (c == '<' || c == '>');
}

char	*filename_trim(char *s, int k, int type)
{
	int		i;
	char	*file;
	char	*file_trimmed = NULL;

	i = 0;
	if (k < 0)
		return (NULL);
	file = malloc(sizeof(char) * (k + 1));
	if (!file)
		return (NULL);
	while (s[i] && i < k)
	{
		file[i] = s[i];
		i++;
	}
	file[i] = '\0';
	return (file);
	file_trimmed = file;
	if (type != 2)
	{
		free(file);
		file = filling_with_nulls(file_trimmed);
	}
	return (file);
}

void	dup_error(int du)
{
	if (du < 0)
		ft_print_error_and_exit("dup2 is < 0", 1);
}

void	close_in_out(int fd)
{
	if ((fd != 1 && fd != 0) && fd > 0)
		close(fd);
}

void	func_for_reds(t_cmd *cmd_node, t_red *red_node, int yep)
{
	if (red_node->type == INPUT_REDIRECTION)
	{
		close_in_out(cmd_node->fd_in);
		cmd_node->fd_in = open(red_node->file, O_RDONLY);
	}
	else if (red_node->type == HEREDOC && yep)
	{
		close_in_out(cmd_node->fd_in);
	}
	else if (red_node->type == APPEND_REDIRECTION)
	{
		close_in_out(cmd_node->fd_out);
		cmd_node->fd_out = open(red_node->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (red_node->type == OUTPUT_REDIRECTION)
	{
		close_in_out(cmd_node->fd_out);
		cmd_node->fd_out = open(red_node->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (cmd_node->fd_in == -1 || cmd_node->fd_out == -1)
		ft_print_error_and_exit("file not found\n", EXIT_FAILURE);
}

void	red_big_loop(t_red_lst *red_lst, t_cmd *cmd, int yep)
{
	t_red	*cur;

	cur = red_lst->head;
	while (cur)
	{
		func_for_reds(cmd, cur, yep);
		cur = cur->next;
	}
}
