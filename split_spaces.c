/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:38:37 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/17 17:51:54 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count(char *s)
{
	int i = 0;
	int count = 0;
	while (s[i])
	{
		if (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
		{
			while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
				i++;
			count++;
		}
		if (!s[i])
			break;
		i++;
	}
	return (count);
}

char *word_alloc(char *s)
{
	char *word;
	int i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	word = (char *)malloc(sizeof(char) * i + 1);
	if (!word)
		return NULL;
	i = 0;
	while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return word;
}

char	**split2(char *s)
{
	int i = 0;
	char **arr;
	arr = (char **)malloc(sizeof(char *) * count(s) + 1);
	if (!s)
		return 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
			s++;
		if (*s && (*s != ' ' && *s != '\t' && *s != '\n'))
		{
			arr[i] = word_alloc(s);
			if (!arr[i])
				return (NULL);
			i++;
		}
		while (*s && (*s != ' ' && *s != '\t' && *s != '\n'))
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
