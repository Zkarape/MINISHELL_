/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:06:39 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/10 14:35:06 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lst_print(t_env_lst *list)
{
	t_env	*cur;

	cur = list->head->next;
	while (cur->next)
	{
		if (cur->data && !(cur->data[1] == '?' && cur->data[2] == '\0'))
			printf("%s\n", cur->data);
		cur = cur->next;
	}
}

t_env	*env_def_initialize(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = NULL;
	node->idx = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env_lst	*env_lst_construct(void)
{
	t_env_lst	*new_list;

	new_list = malloc(sizeof(t_env_lst));
	if (!new_list)
		return (NULL);
	new_list->head = env_def_initialize();
	new_list->tail = env_def_initialize();
	new_list->head->next = new_list->tail;
	new_list->tail->prev = new_list->head;
	new_list->size = 0;
	return (new_list);
}

t_env	*env_initialize(char *data, t_env *next, t_env *prev)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = next;
	node->prev = prev;
	node->idx = -1;
	return (node);
}
