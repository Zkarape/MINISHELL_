/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:03:34 by aivanyan          #+#    #+#             */
/*   Updated: 2023/01/31 19:37:04 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(int sig)
{
	printf("ctrl+c is pressed %d\n", sig);
	exit(0);
}

void	sig_handle(int a)
{
	if (a == 1)
		signal(SIGINT, print);
}
