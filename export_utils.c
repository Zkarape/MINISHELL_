/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:37:14 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/16 17:53:53 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void swap(t_env *a, t_env *b)
{
    char *temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void sort(t_env_lst	*exp_lst)
{
	int		swapped;
	t_env	*head;
	t_env	*ptr1;
	t_env	*lptr = NULL;

	head = exp_lst->head->next;
	if (head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
	   	{
			if (ft_strncmp(ptr1->data, ptr1->next->data, ft_strlen(ptr1->data)) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

char	*equality_out_of_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (is_quote(s[i]))
			i += find_last_quote(&s[i], s[i]);
		else if (s[i] == '=')
		{
			if (!error_checks_for_var(s, i))
				return (NULL);
			return (&s[i + 1]);
		}
	}
	return (NULL);
}

char	*adding_quotes(char *s)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	j = 1;
	if (!s)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s) + 3));
	dst[0] = '"';
	while (s[++i])
	{
		dst[j] = s[i];
		j++;
	}
	dst[j] = '"';
	dst[++j] = '\0';
	return (dst);
}

t_env	*is_in_env_or_not(t_env_lst *env_lst, char *arg)
{
	t_env	*cur;
	int		k;

	cur = env_lst->head->next;
	while (cur->next)
	{
		k = until_equal_sign(cur->data);
		if (!ft_strncmp(cur->data, arg, k) && k == ft_strlen(cur->data))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_env	*is_in_export_or_not(t_env_lst *exp_lst, char *arg)
{
	t_env	*cur;
	int		k;

	cur = exp_lst->head->next;
	while (cur->next)
	{
		k = until_equal_sign("suidjxc =");
		if (!ft_strncmp(&cur->data[11], arg, k) && k == ft_strlen(&cur->data[11]))
		{
			printf("arg == %s\n", &cur->data[11]);
			return (cur);
		}
		cur = cur->next;
	}
	return (NULL);
}
