#include "minishell.h"

char	*equality_out_of_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (is_quote(s[i]))
			i += find_last_quote(&s[i], s[i]);
		else if (s[i] == '=')
		{
			if (!error_checks_for_var(s, i))
				return (NULL);
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

void	ft_export(t_cmd *cmd, t_env_lst *env_lst, t_env_lst *exp_lst)
{
	int	i;

	i = 0;
	while (cmd->no_cmd[++i])
	{
		if (equality_out_of_quotes(cmd->no_cmd[i]))
			env_lst_add_last(env_lst, cmd->no_cmd[i]);
		export_pars(cmd->no_cmd[i], exp_lst);
	}
	env(exp_lst);
}

void	export_pars(char *s, t_env_lst *exp_lst)
{
	int			i;
	char		*data;
	char		*unquoted;
	char		*quoted;

	i = 0;
	data = NULL;
	unquoted = equality_out_of_quotes(s);
	quoted = adding_quotes(unquoted);
	data = ft_strjoin(s, quoted, ft_strlen(quoted),
		0, ft_strlen(s) - ft_strlen(unquoted));
	env_lst_add_last(exp_lst, ft_strjoin("declare -x ", data, ft_strlen(data), 0, 11));
}

t_env_lst	*exp_cpy_env(t_env_lst *env_lst)
{
	t_env		*cur;
	t_env_lst	*exp_lst;

	cur = env_lst->head->next;
	exp_lst = env_lst_construct();
	while (cur->next)
	{
		export_pars(cur->data, exp_lst);
		cur = cur->next;
	}
	return (exp_lst);
}

















