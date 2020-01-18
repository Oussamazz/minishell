/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:03:44 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/16 17:29:43 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	free_list_msh(t_node **head)
{
	t_node *current;
	t_node *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		ft_strdel(&(current->data));
		free(current);
		current = next;
	}
	*head = NULL;
}

int     main(int ac, char **av, char **envp)
{
    t_node *env;
    env = NULL;
    stock_env(envp, &env);
    (void)ac;
	signal(3, ft_ctrlc);
    msh_loop(&env);
    free_list_msh(&env);
    return(1);
}