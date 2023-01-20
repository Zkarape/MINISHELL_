/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:34 by aivanyan          #+#    #+#             */
/*   Updated: 2023/01/20 14:26:29 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\f'
		|| c == '\n' || c == '\r' || c == '\v');
}

void	ft_putstr_fd(char *s, int fd, int fl)
{
	write(fd, s, ft_strlen(s));
	if (fl)
		write(fd, "\n", 1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		;
	return (i);
}

char	*get_environment(char *name, char **g_envp)
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

char	*ft_strjoin_m(char *s1, char *s2)
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

char	*ft_strjoin(char *s1, char *s2, int start, int end, int len)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc((len + start - end + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	while (end < start && s2)
	{
		dst[i] = s2[end];
		i++;
		end++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*str12;
	char	*str123;

	str12 = ft_strjoin_m(str1, str2);
	str123 = ft_strjoin_m(str12, str3);
	free(str12);
	return (str123);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
