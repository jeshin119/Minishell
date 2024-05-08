#include "include/minishell.h"
#include "include/my_deque.h"

int main(int ac,char **av ,char **envp){
	for(int i=0;i<256;i++){
		perror("file");
		// printf("%s : %d\n",strerror(i),i);
	}
}
