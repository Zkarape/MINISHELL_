/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:51:16 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/31 18:51:50 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nothing_but_int(char *str)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return (0);
	while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
		;
	if (str[0] == '-' || str[0] == '+')
		while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
			;
	if (!str[i])
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	long long	res;
	int			min;
	int			i;

	min = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == 0)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if ((res * min) > 2147483647 || (res * min) < -2147483648)
		ft_print_error_and_exit("INT IS NOT UNLIMIT!!\n", 1);
	return (res * min);
}

void	ft_exit(t_cmd *cmd_head)
{
	long long	x;
	int			i;

	i = -1;
	if (!nothing_but_int(cmd_head->no_cmd[1]))
		ft_print_error_and_exit("exit: numeric argument required\n", 1);
	while (cmd_head->no_cmd[++i])
		;
	if (i > 2)
		ft_print_error_and_exit("exit: too many arguments\n", 1);
	x = ft_atoi(cmd_head->no_cmd[1]);
	exit(x % 256);
}
