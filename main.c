/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:35:38 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/15 23:11:11 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int a(void)
{
	return 0;
}

int	main(int ac, char **av, char **env)
{
	t_args	args;

	(void)ac;
	(void)av;
//	set_get_attr();
	parsing(env, &args);
}
