#include "include/minishell.h"
#include "include/my_deque.h"
void	_echo(t_subtree * subtree)
{
	char	*opt;
	char	*str;
	int		i;
	// for(int i=0;subtree->opt[i]!=0;i++){
	// 	printf("%s\n",subtree->opt[i]);
	// }
	i=-1;
	while(subtree->opt[++i]);
	if (i == 1 && ft_strncmp(subtree->opt[1], "-n", 3))
		ft_putstr("\n");
	else if (i == 1 && ft_strncmp(subtree->opt[1], "-n", 3) == 0)
		;
	else if (i == 2 && ft_strncmp(subtree->opt[1], "-n", 3)){
		ft_putstr(subtree->opt[1]);
		write(1, "\n", 1);
	}
	else if (i == 2 && ft_strncmp(subtree->opt[1], "-n", 3) == 0)
		ft_putstr(subtree->opt[1]);
	// exit(EXIT_SUCCESS);
}

void	check_leak(void)
{
	system("leaks a.out");
}
int main(int ac,char **av ,char **envp){
	char *buf = readline(">");
	_echo
}
