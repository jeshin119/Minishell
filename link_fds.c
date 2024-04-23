/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:33:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 12:35:15 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	traverse_tree(t_tree *tree)
{
	if (tree->next_left && tree->next_right == 0) // 왼쪽이 있는데 오른쪽 없으면 왼쪽만들어감.
	{
		traverse_tree(tree->next_left); 
		fork_link_exec(tree);
	}
	if (tree->next_left && tree->next_right)//왼쪽 오른쪽 자식 둘다 있으면 왼쪽 들어가고 오른쪽 들어감.
	{
		traverse_tree(tree->next_left);
		fork_link_exec(tree);
		traverse_tree(tree->next_right);
	}
	else {
		fork_link_exec(tree);
	}
}

static int get_fd(t_tree *tree)
{
	if (tree->ctrl_token == PIPE) // pipe면 pass!
		return (EXIT_SUCCESS);
	if (tree->ctrl_token == HERE_DOC)
		return (open_heredoc_n_return(tree));
	if (tree->ctrl_token == LEFT)
		return (open_infile_n_return(tree));
	if (tree->ctrl_token == RIGHT)
		return (open_outfile_n_return(tree));
	if (tree->ctrl_token == D_RIGHT)
		return (care_appending_n_return(tree));
}

typedef struct s_fd_lst
{
	int **pipe_tab;
	int	p_idx;

}	t_fd_lst;

int	open_n_link_fds(t_tree *tree)
{
	int	**pipe_tab;
	int	pipe_num;

	if (tree == 0 || tree->end_flag)
		return (EXIT_SUCCESS); //return success ? : tre 에 아무것도 들어오지 않았을 때 echo $? : 0임. 

	pipe_num = get_pipe_num_from_tree; // 파이프 수 구하기.
	pipe_tab = open_pipes(pipe_num); // 파이프 수만큼 파이프를 열어놓음.
	if (pipe_tab)
		return (EXIT_FAILURE);
	
	traverse_tree(tree);  //만나는 순서대로 리스트에 넣자 
	//close_all_pipe,,
	return (EXIT_SUCCESS);

}
