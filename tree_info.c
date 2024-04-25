/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:09:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/25 17:43:35 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int init_tree_info(t_tree *tree, t_tree_info *tree_info)
{
	// if (tree == 0 || tree->end_flag)
	// 	return (EXIT_SUCCESS); //return success ? : tre 에 아무것도 들어오지 않았을 때 echo $? : 0임. 
	tree_info->sbt_lst = (t_sbt_lst *)malloc(sizeof(t_sbt_lst));
	tree_info->pipe_num = get_pipe_num_from_tree(tree); // 파이프 수 구하기.
	if (open_pipes(tree_info->pipe_num,&(tree_info->pipe_tab))) // 파이프 수만큼 파이프를 열어놓음.
		return (EXIT_FAILURE);
	tree_info->sbt_lst->head = 0;
	tree_info->sbt_lst->tail = 0;
	return (EXIT_SUCCESS);
}

// void	init_sbtl(t_sbt_lst *sbtl)
// {
// 	sbtl->head = 0;
// }

// int	is_empty_sbtl(t_sbt_lst *sbtl)
// {
// 	if (sbtl->head == 0)
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }

// void	push_front_sbtl(t_sbt_lst *sbtl, char* name, char *val)
// {
// 	t_node	*new;

// 	if (sbtl == 0)
// 		return ;
// 	new = (t_node *)malloc(sizeof(t_node));
// 	if (!new)
// 		return ;
// 	new->name = name;
// 	new->val = val;
// 	new->next = sbtl->head;
// 	if (is_empty_dq(sbtl))
// 		sbtl->tail = new;
// 	else
// 		sbtl->head->prev = new;
// 	new->prev = 0;
// 	sbtl->head = new;
// }

// void	push_back_dq(t_dq *dq, char* name, char *val)
// {
// 	t_node	*new;

// 	if (dq == 0)
// 		return ;
// 	new = (t_node *)malloc(sizeof(t_node));
// 	if (!new)
// 		return ;
// 	new->name = name;
// 	new->val = val;
// 	new->prev = dq->tail;
// 	if (is_empty_dq(dq))
// 		dq->head = new;
// 	else
// 		dq->tail->next = new;
// 	new->next = 0;
// 	dq->tail = new;
// 	dq->size++;
// }

// void	print_all_dq(t_dq *dq)
// {
// 	t_node	*here;

// 	here = dq->head;
// 	while (here)
// 	{
// 		ft_putstr_fd(here->name, 1);
// 		write(1,"=",1);
// 		ft_putstr_fd(here->val, 1);
// 		write(1, "\n", 1);
// 		here = here->next;
// 	}
// }