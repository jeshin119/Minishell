/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:26:10 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/26 16:33:53 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	prt_sbtl(t_tree_info *trif)
{
	t_subtree *here;
	
	here = trif->sbt_lst->head;
	printf("\n*********************************\n");
	while (here)
	{
		printf("cmd : %s,\t",here->cmd);
		if (here->opt)
		{
			printf("opt : ");
			for(int i=0;here->opt[i]!=0;i++)
				printf("%s ",here->opt[i]);
			printf(",\t");
		}
		printf("infile : %s,\t",here->infile);
		printf("outfile : %s.\n",here->outfile);
		here= here->next;
	}
	printf("\n*********************************\n");
}

void	free_subtree(t_subtree *sbtr)
{
	int i;

	if (sbtr->cmd)
	{
		free(sbtr->cmd);
		sbtr->cmd = 0;
	}
	if (sbtr->opt)
	{
		i = -1;
		while((sbtr->opt)[++i])
			free((sbtr->opt)[i]);
		free(sbtr->opt);
	}
	if (sbtr->infile)
	{
		free(sbtr->infile);
		sbtr->infile = 0;
	}
	if (sbtr->outfile)
	{
		free(sbtr->outfile);
		sbtr->outfile = 0;
	}
	if (sbtr->is_heredoc)
		unlink(".here_doc_tmp_f");
}