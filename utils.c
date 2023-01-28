/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:34 by aivanyan          #+#    #+#             */
/*   Updated: 2023/01/28 20:41:48 by aivanyan         ###   ########.fr       */
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

char	*ft_strcpy(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	printf("stcss  == %s\n", src);
	while (src && *src)
	{
		*temp = *src;
		src++;
		temp++;
	}
	*temp = '\0';
	printf("temp == %s\n", temp);
	return (dest);
}
#include <string.h>

char	**from_lst_to_dbl(t_env_lst *env_lst)
{
	int		i;
	char	**arr;
	t_env	*env;

	i = 0;
	env = env_lst->head->next;
	arr = malloc(sizeof(char *) * (env_lst->size + 1));
	while (env->next)
	{
		arr[i] = malloc(sizeof(char) * (ft_strlen(env->data) + 1));
		strcpy(arr[i++], env->data);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

char	*ft_str_tolower(char *s)
{
	int		i;
	char	*str;

	i = -1;
	str = malloc(sizeof(ft_strlen(s) + 1));
	while (s[++i])
		str[i] = ft_tolower(s[i]);
	str[i] = '\0';
	return (str);
}
