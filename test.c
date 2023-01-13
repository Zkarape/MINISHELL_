#include "minishell.h"
#include <string.h>
int main(int ac, char **av)
{
	printf("%s\n", equality_out_of_quotes(av[1]));
	printf("%s\n", adding_quotes("'aaaaa'"));
}
