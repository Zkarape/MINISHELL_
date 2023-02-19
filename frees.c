#include "minishell.h"

void	pipefds_free(pid_t (*pipefds)[2], int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(pipefds[i]);
	}
	free(pipefds);
}

void env_def_free(t_env *node)
{
	if (node)
		free(node);
}

void env_lst_destruct(t_env_lst *list)
{
	t_env *cur = list->head;

	while (cur)
	{
		t_env *tmp = cur->next;
		env_def_free(cur);
		cur = tmp;
	}
	free(list);
}
