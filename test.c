#include "include/minishell.h"
#include "include/my_deque.h"
static int	has_opt_err(char *s)
{
	int	has_space;
	int	has_num;

	has_space = 0;
	has_num = 0;
	while (*s)
	{
		if (!ft_isdigit(*s) && !ft_isspace(*s))
			return (TRUE);
		if (has_num == 1 && has_space == 1 && !ft_isspace(*s))
			return (TRUE);
		if (ft_isdigit(*s))
			has_num = 1;
		if (ft_isspace(*s))
			has_space = 1;
		s++;
	}
	if (has_num == 0)
		return (TRUE);
	return (FALSE);
}
int main(int ac,char **av ,char **envp){
	char *str1="h"; //255 //numeric
	char *str2="h123"; //255 numeric
	char *str3="123hh"; //255 numsric
	char *str4="1    ";
	char *str5="     1";
	char *str6="12 45";//255 numsric
	printf("str : %s, result : %d\n",str1,has_opt_err(str1));
	printf("str : %s, result : %d\n",str2,has_opt_err(str2));
	printf("str : %s, result : %d\n",str3,has_opt_err(str3));
	printf("str : %s, result : %d\n",str4,has_opt_err(str4));
	printf("str : %s, result : %d\n",str5,has_opt_err(str5));
	printf("str : %s, result : %d\n",str6,has_opt_err(str6));
}
