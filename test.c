#include "include/minishell.h"
#include "include/my_deque.h"
char	*get_path(char *cmd, t_dq *env)
{
	t_node *start=env->head;
	char *path;
	while(start){
		if (ft_strncmp(start->name,"PATH",4)==0)
			break;
		start=start->next;
	}
	char **tab = ft_split(start->val, ':');
	int i=-1;
	while(tab[++i]){
		char *tmp = ft_strjoin(tab[i],"/");
		free(tab[i]);
		tab[i] = tmp;
	}
	int i=-1;
	while(tab[++i]){
		path = ft_strjoin(tab[i],cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tab(tab);
			return (path);
		}
		free(path);
	}
	free_tab(tab);
	perror("path error");
	exit(127);
	return (NULL);
}
int main(int ac,char **av ,char **envp){
	t_dq env;
	make_my_env(envp,&env);
	char *s = get_path("0",&env);
	printf("%s\n",s);
}