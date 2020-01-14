/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:51:46 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/12 20:18:59 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exist(t_node **head, char *str)
{
	size_t	str_len;
	t_node 	*tmp;

	str_len = ft_strlen_char(str, '=');
	tmp = *head;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->data, str, str_len))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
