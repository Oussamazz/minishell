/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:06:34 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/14 17:06:54 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push(t_node **head, char *data)
{
	t_node *new;

	new = NULL;
	if (!(new = (t_node*)ft_memalloc(sizeof(t_node))))
		return ;
	new->data = ft_strdup(data);
    new->flag = false;
	new->next = *head;
	*head = new;
	return ;
}

void	append(t_node **head, char *data)
{
	t_node *new;
	t_node *inc;

	new = NULL;
	inc = *head;
	if (!(new = (t_node*)ft_memalloc(sizeof(t_node))))
		return ;
	new->data = ft_strdup(data);
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (inc->next != NULL)
		inc = inc->next;
	inc->next = new;
	return ;
}

int		tablen(char **arr)
{
	int count;

	count = 0;
	while (arr[count] != NULL)
		count++;
	return (count);
}

void		delete_node(t_node **head, char *str)
{
	t_node *temp;
	t_node *prev;

	temp = *head;
	if (temp != NULL && !ft_strncmp(temp->data, str, ft_strlen_char(temp->data, '=')))
	{
		*head = temp->next;
		free(temp->data);
		free(temp);
		return ;
	}
	while (temp != NULL && ft_strncmp(temp->data, str, ft_strlen_char(temp->data, '=')) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	ft_strdel(&(temp->data));
	free(temp);
}

void	stock_env(char **arr, t_node **head)
{
	int i;

	i = tablen(arr) - 1;
    if (i == -1)
        return (push(head, ""));
	while (i >= 0 && arr[i])
	{
		push(head, arr[i]);
		i--;
	}
}
