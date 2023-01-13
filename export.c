#include "minishell.h"

char	*equality_out_of_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (is_quote(s[i]))
			i += find_last_quote(&s[i], s[i]);
		else if (s[++i] == '=')
		{
			error_checks_for_var(s, i);
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

t_env_lst	*ft_export(t_env_lst *env_lst)
{
	t_env_lst	*exp_lst;
	t_env		*env_node;
	char		*data;

	env_node = env_lst->head->next;
	exp_lst = env_lst_construct();
	data = NULL;
	while (env_node->next)
	{
		data = ft_strjoin("declare -x ", env_node->data,
			ft_strlen(env_node->data), 0);
		env_lst_add_last(exp_lst, data);
		env_node = env_node->next;
	}
	env(exp_lst);
	return (exp_lst);
}

void	export_pars(t_cmd *cmd_node, t_env_lst *env_lst, t_env_lst *exp_lst)
{
	int		i;
	char	*data;

	i = -1;
	data = NULL;
	while (cmd_node->no_cmd[++i])
	{
		
		//data = ft_strjoin("")
		env_lst_add_last(exp_lst, data);
	}
}
