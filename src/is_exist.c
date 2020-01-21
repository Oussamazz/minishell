/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:51:46 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/21 19:11:55 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exist(t_node **head, char *str)
{
	size_t	str_len;
	t_node	*tmp;

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

int		check_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
