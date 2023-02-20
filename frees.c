/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:41:39 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/19 21:17:33 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_a(t_args *a, int f)
{
	if (a->env)
		dbl_free(a->env);
	if (a->pipefds && f)
		pipefds_free(a->pipefds);
	if (a->file)
		free(a->file);
	if (a->pids)
		free(a->pids);
}

void	pipefds_free(pid_t (*pipefds)[2])
{
	if (pipefds)
		free(pipefds);
}

void	dbl_free(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
	{
		free(arr[i]);
	}
	if (arr)
		free(arr);
}

void env_def_free(t_env *node)
{
	if (node)
		free(node);
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
}

void node_def_free(t_node *node)
{
	if (node)
	{
		if (node->data)
			free(node->data);
		free(node);
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
}

void red_def_free(t_red *node)
{
	if (node)
	{
		if (node->file)
			free(node->file);
		free(node);
	}
}

void red_lst_destruct(t_red_lst *list)
{
	t_red *cur;
	t_red *tmp;

	tmp = NULL;
	if (list)
		cur = list->head;
	else
		cur = NULL;
	while (cur)
	{
		tmp = cur->next;
		red_def_free(cur);
		cur = tmp;
	}
	free(list);
}

void cmd_def_free(t_cmd *node)
{
	if (node)
	{
		if (node->args)
			free(node->args);
		if (node->no_cmd)
			dbl_free(node->no_cmd);
		red_lst_destruct(node->red_lst);
		free(node);
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
}
