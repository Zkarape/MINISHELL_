#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	//int i;
	t_cmd	*cmd_node = NULL;

	//i = -1;
	//int i = -1;
	//char *s = readline("minishell$");
	//printf("s is : %s\n", s);
//	expand(s);
	parsing(env);
//	grouping_with_red(group_until_pipe(s), getting_env(env));
//	printf("%s\n", expand(s, getting_env(env)));
	//char **arr = ft_split(s);
	//char *cpy;
	//while (arr[++i])
	//{
///	printf("sizeof %lu\n", sizeof(d)/sizeof(int));
	//	cpy = strcpy_noquotes(arr[i], '"');
	//	printf("after %s\n", cpy);
	//printf("%d",return_type('>', '>'));
}
