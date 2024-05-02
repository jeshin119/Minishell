#include "include/minishell.h"
#include "include/my_deque.h"

int	is_all_n(char *s)
{
	int	i;

	if (s == 0)
		return (FALSE);
	if (ft_strncmp(s, "-n", 3) == 0)
		return (TRUE);
	i = -1;
	if (s[++i] != '-')
		return (FALSE);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (FALSE);
	}
	return (TRUE);
}

int main(int ac,char **av ,char **envp){
	while(1){
		char *buf = readline(">");
		printf("no_lf : %d\n",is_all_n(buf));

	}
}
