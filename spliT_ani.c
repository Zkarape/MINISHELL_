/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliT_ani.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:49:14 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/17 17:51:45 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_count(char const *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char const	*ft_start(char const *s, char c)
{
	while (*s)
	{
		if (*s != c)
			return (s);
		s++;
	}
	return (NULL);
}

static char const	*ft_end(char const *s, char c)
{
	while (*s)
	{
		if (*s != c && ((*(s + 1) == c) || (*(s + 1) == '\0')))
			return (s);
		s++;
	}
	return (NULL);
}

static int	ft_check_alloc(char **split, char *str, int index)
{
	if (str)
		return (0);
	while (index >= 0)
		free(split[index--]);
	free(split);
	return (1);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	**split(char const *s, char c)
{
	char	**split;
	int		count;
	int		i;
	int		end;

	count = ft_count(s, c);
	split = ft_calloc((count + 1), sizeof(s));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		s = ft_start(s, c);
		end = ft_end(s, c) - s + 1;
		split[i] = malloc((end + 1) * sizeof(char));
		if (ft_check_alloc(split, split[i], i))
			return (NULL);
		ft_strlcpy(split[i++], s, end + 1);
		s += end;
	}
	return (split);
}
