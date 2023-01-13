#include "minishell.h"

//checking, ><, <<<
int	return_type(char c, char c_next)
{
	if (c == '<')
	{
		if (c_next == '<')
			return (2);
		else
			return (1);
	}
	if (c == '>')
	{
		if (c_next == '>')
			return (3);
		else
			return (4);
	}
	return (8);
}

void	find_start_end(char *s, t_cmd *cmd_node, t_red_lst *red_lst)
{
	int		i;
	int		start;
	int		end;
	char	*str;
	int		type;
	char	*tmp;
	char	*file;

	i = -1;
	start = 0;
	end = -1;
	str = NULL;
	type = 0;
	while(s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i += find_last_quote(&s[i], s[i]);
		else if (is_red(s[i]))
		{
			tmp = str;
			str = ft_strjoin(tmp, s, i, end + 1);
			type = return_type(s[i], s[i + 1]);
			if (type == 2 || type == 3)
				i++;
			while (ft_is_space(s[i]))
				i++;
			start = i;
			while (s[i + 1] && !ft_is_space(s[i + 1]) && !is_red(s[i + 1]))
			 	i++;
			end = i;
			file = filename_trim(&s[start + 1], end - start, type);
			red_lst_add_last(red_lst, file, type);
		}
	}
	cmd_node->args = ft_strjoin(str, s, i, end + 1);
	printf("args == %s\n", cmd_node->args);
}

void	one_cmd_init(t_node *node, t_cmd_lst *cmd_lst, t_env_lst *env_lst)
{
	char		*s;
	int			i;
	t_red_lst	*red_lst;

	i = -1;
	s = node->data;
	cmd_lst_add_last(cmd_lst);
	red_lst = red_lst_construct();
	find_start_end(s, cmd_lst->tail, red_lst);
	cmd_lst->tail->red_lst = red_lst;
	big_loop(cmd_lst->tail, env_lst);
	red_big_loop(red_lst, cmd_lst->tail);
}

t_cmd_lst	*grouping_with_red(t_list *pipe_group, t_env_lst *env_lst)
{
	int			i;
	t_node		*cur;
	t_cmd_lst	*cmd_lst;
	t_red_lst	*red_lst;

	i = -1;
	cmd_lst = cmd_lst_construct();
	cur = pipe_group->head;
	while (cur)
	{
		one_cmd_init(cur, cmd_lst, env_lst);
		cur = cur->next;
	}
	return (cmd_lst);
}
