/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 21:17:41 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 17:55:20 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_list(t_node **head)
{
	t_node *cur;

	cur = *head;
	while (cur)
	{
		if (*(cur->data) != '\0')
			ft_putendl_fd(cur->data, 1);
		cur = cur->next;
	}
	return ;
}

void		git(char *tmp)
{
	if (tmp)
	{
		ft_putchar('(');
		ft_putstr_color(tmp, "\033[0;35m");
		ft_putstr_color("*", "\033[0;33m");
		ft_putchar(')');
		ft_putstr("\033[0m");
	}
}
