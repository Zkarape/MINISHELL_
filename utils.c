/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:34 by aivanyan          #+#    #+#             */
/*   Updated: 2022/10/29 19:16:53 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_environment(char *name)
{
	int	i;

	i = 0;
	while (g_envp[i])
	{
		if (!ft_strncmp(g_envp[i], name, ft_strlen(name)))
			return (g_envp[i] + ft_strlen(name));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;

	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		join[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		join[i] = *s2;
		s2++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*str12;
	char	*str123;

	str12 = ft_strjoin(str1, str2);
	str123 = ft_strjoin(str12, str3);
	free(str12);
	return (str123);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*str1;
	unsigned const char	*str2;

	str1 = (unsigned const char *)s1;
	str2 = (unsigned const char *)s2;
	while ((*str1 || *str2) && n > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		n--;
		str1++;
		str2++;
	}
	return (0);
}

void	ft_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
