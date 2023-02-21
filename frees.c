/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:41:39 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 21:25:18 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_a(t_args *a, int f)
{
	dbl_free(a->env);
	pipefds_free(a->pipefds);
	free(a->file);
	free(a->pids);
	a->env = NULL;
	a->pipefds = NULL;
	a->file = NULL;
	a->pids = NULL;
}

void	pipefds_free(pid_t (*pipefds)[2])
{
	free(pipefds);
	pipefds = NULL;
}

void	dbl_free(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void env_def_free(t_env *node)
{
	free(node);
	node = NULL;
}

void env_lst_destruct(t_env_lst *list)
{
	t_env *cur;
	t_env *tmp;

	tmp = NULL;
	cur = list->head->next;
	while (cur)
	{
		tmp = cur->next;
		env_def_free(cur);
		cur = tmp;
	}
	free(list);
	list = NULL;
}

void node_def_free(t_node *node)
{
	if (node)
	{
		free(node->data);
		free(node);
		node = NULL;
	}
}

void lst_destruct(t_list *list)
{
	t_node *cur;
	t_node *tmp;

	tmp = NULL;
	if (list)
		cur = list->head;
	else
		cur = NULL;
	while (cur)
	{
		tmp = cur->next;
		node_def_free(cur);
		cur = tmp;
	}
	free(list);
	list = NULL;
}

void red_def_free(t_red *node)
{
	if (node)
	{
		free(node->file);
		free(node);
		node->file = NULL;
		node = NULL;
	}
}

void red_lst_destruct(t_red_lst *list)
{
	t_red *cur;
	t_red *tmp;

	tmp = NULL;
	cur = NULL;
	if (list)
		cur = list->head;
	while (cur)
	{
		tmp = cur->next;
		red_def_free(cur);
		cur = tmp;
	}
	free(list);
	list = NULL;
}

void cmd_def_free(t_cmd *node)
{
	if (node)
	{
		free(node->args);
		red_lst_destruct(node->red_lst);
		dbl_free(node->no_cmd);
		free(node);
		node->args = NULL;
		node->red_lst = NULL;
		node->no_cmd = NULL;
		node = NULL;
	}
}

void cmd_lst_destruct(t_cmd_lst *list, t_cmd *until)
{
	t_cmd *cur;
	t_cmd *tmp;

	tmp = NULL;
	if (list)
		cur = list->head;
	else
		cur = NULL;
	while (cur != until)
	{
		tmp = cur->next;
		cmd_def_free(cur);
		cur = tmp;
	}
	free(until);
	free(list);
	until = NULL;
	list = NULL;
}
