#include "include/minishell.h"
#include "include/my_deque.h"
//cc -lreadline test.c ./parse/my_deque.c ./parse/my_deque2.c ./libft/libft.a 으로 컴파일가능
//할당 잘 되는 것 같은디??
void cl(void){
	system("leaks a.out");
}
int main(){
	t_dq dq;
	while(1){
		char *buf = readline(">>");

		printf("push %s to deque\n",buf);
		push_back_dq(&dq,buf,0);
		if (buf == 0)
			break;
	}
	t_node *start=dq.head;
	while(start){
		printf(">>> %s \n",start->name);
		start=start->next;
	}
	// clear_dq(&dq);
	atexit(cl);
	return 0;
}