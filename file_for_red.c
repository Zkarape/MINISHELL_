/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:17:00 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/21 22:03:47 by zkarapet         ###   ########.fr       */
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
	printf("file == %s\n", file);
	return (file);
}

void	dup_error(int du)
{
	if (du < 0)
		ft_print_error_and_exit("dup2 is < 0", 1);
}

void	func_for_reds(t_cmd *cmd_node, t_red *red_node, int yep)
{
//	int	fd_in;
//	int	fd_out;

//	fd_in = -4;
//	fd_out = -3;
//	if (cmd_node->fd_in != 0)
//		close(cmd_node->fd_in);
//	if (cmd_node->fd_out != 1)
//		close(cmd_node->fd_out);
	if (red_node->type == INPUT_REDIRECTION)
		cmd_node->fd_in = open(red_node->file, O_RDONLY);
	else if (red_node->type == HEREDOC && yep)
	{
		cmd_node->fd_in = open("/Users/zkarapet/Desktop/MINISHELL_/k5", O_RDWR | O_APPEND, 0644);
	}
	else if (red_node->type == APPEND_REDIRECTION)
		cmd_node->fd_out = open(red_node->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (red_node->type == OUTPUT_REDIRECTION)
	{
		printf("cmd_in == %d, cmd_out == %d\n", cmd_node->fd_in, cmd_node->fd_out);
		cmd_node->fd_out = open(red_node->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		printf("after cmd_in == %d, after cmd_out == %d\n", cmd_node->fd_in, cmd_node->fd_out);
	}
	if (cmd_node->fd_in == -1 || cmd_node->fd_out == -1)
		ft_print_error_and_exit("file not found\n", EXIT_FAILURE);
//	if (cmd_node->fd_in && yep == 0)
//	{
//		printf("ALOOOOOY\n");
//		//dup_error(dup2(fd_in, cmd_node->fd_in));
//		//cmd_node->fd_in = fd_in;
//		close(fd_in);
//		if (fd_out != -3)
//			close(fd_out);
//	}
//	if (cmd_node->fd_out)
//	{
//		printf("ALOOOY 222\n");
// 	 //	dup2(fd_out, cmd_node->fd_out);
//	 	//cmd_node->fd_out = fd_out;
//		close(fd_out);
//		if (fd_in != -4)
//			close(fd_in);
//	}
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
