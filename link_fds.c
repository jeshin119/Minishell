/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:33:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/25 17:40:09 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

//sudo
// void	traverse_tree(t_tree *tree)
// {
// 	if (tree->next_left && tree->next_right == 0) // 왼쪽이 있는데 오른쪽 없으면 왼쪽만들어감.
// 	{
// 		traverse_tree(tree->next_left); 
// 		fork_link_exec(tree);
// 	}
// 	if (tree->next_left && tree->next_right)//왼쪽 오른쪽 자식 둘다 있으면 왼쪽 들어가고 오른쪽 들어감.
// 	{
// 		traverse_tree(tree->next_left);
// 		fork_link_exec(tree);
// 		traverse_tree(tree->next_right);
// 	}
// 	else {
// 		fork_link_exec(tree);
// 	}
// }

//cat <a >b <<c >>d 를 하면 c의 결과가 d에 작성됨.

void t2(t_tree *tree, t_sbt_lst *sbtl)//서브트리 리스트를 받아 리스트 맨 뒤에 서브트리 노드를 만드는 함수
{
	t_tree	*left_child;
	t_tree	*right_child;
	t_subtree	*new;

	if (tree == 0)
		return ;

	new = (t_subtree *)malloc(sizeof(t_subtree));

	new->cmd=0;
	new->opt=0;
	new->infile_fd=0;
	new->outfile_fd=1;
	new->next=0;
	new->prev=0;


	left_child = tree;
	right_child = tree->next_right;
	
	while (left_child)
	{
		if (left_child->ctrl_token == 0)
		{
			new->cmd = get_nth_token_from_lst(left_child, (left_child->tk_idx_set)[0]);
			new->opt = get_opt_from_lst(left_child);
			new->infile_fd = care_redirection(left_child->prev);
			break;
		}
		left_child = left_child->next_left;
	}
	while (right_child)
	{
		if(right_child->next_right==0 && right_child->next_right == 0)
		{
			new->outfile_fd =care_redirection(right_child);
			break;
		}
		right_child = right_child->next_right;
	}
	if (sbtl->head == 0){
		sbtl->head = new;
		sbtl->tail = new;
		new->next = 0;
		new->prev = 0;
	}
	else{
		t_subtree *here = sbtl->head;
		while (here->next){
			here=here->next;
		}
		here->next = new;
		new->prev = here;
		new->next = 0;
	}
}

void t1(t_tree *tree, t_sbt_lst *sbtl)//트리를 돌면서 서브트리리스트를 만드는 함수
{
	if (tree->ctrl_token != PIPE)
	{
		t2(tree,sbtl);
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right == 0)
	{
		t2(tree->next_left,sbtl); 
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right)
	{
		t2(tree->next_left,sbtl);
		t1(tree->next_right,sbtl);
	}
	if (tree->ctrl_token == PIPE && tree->next_left == 0 && tree->next_right == 0)
	{
		;//cat < qeustion.txt | 이후에 입력을 새로 받음. 새로 wc -l 와 같이 명령주면 합쳐서 실행해야함.
	}
}

int	make_subtree_lst(t_tree *tree, t_sbt_lst *sbtl)
{
	t1(tree, sbtl);  //트리 순회하면서 정보 갱신
	return (EXIT_SUCCESS);
}
