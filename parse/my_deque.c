/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:01:46 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 15:20:55 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/my_deque.h"

void	init_dq(t_dq *dq)
{
	dq->head = 0;
	dq->tail = 0;
	dq->size = 0;
}

int	is_empty_dq(t_dq *dq)
{
	if (dq->head == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	push_front_dq(t_dq *dq, char* name, char *val)
{
	t_node	*new;

	if (dq == 0)
		return ;
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return ;
	new->name = name;
	new->val = val;
	new->next = dq->head;
	if (is_empty_dq(dq))
		dq->tail = new;
	else
		dq->head->prev = new;
	new->prev = 0;
	dq->head = new;
	dq->size++;
}

void	push_back_dq(t_dq *dq, char* name, char *val)
{
	t_node	*new;

	if (dq == 0)
		return ;
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return ;
	new->name = name;
	new->val = val;
	new->prev = dq->tail;
	if (is_empty_dq(dq))
		dq->head = new;
	else
		dq->tail->next = new;
	new->next = 0;
	dq->tail = new;
	dq->size++;
}

void	print_all_dq(t_dq *dq)
{
	t_node	*here;

	here = dq->head;
	while (here)
	{
		ft_putstr_fd(here->name, 1);
		write(1,"=",1);
		ft_putstr_fd(here->val, 1);
		write(1, "\n", 1);
		here = here->next;
	}
}
