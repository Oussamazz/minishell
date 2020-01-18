/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 10:56:07 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/15 18:06:05 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		words(char *str)
{
	int i;
	bool flag;
	int count;

	i = 0;
	flag = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] != ';' && str[i])
		{
			i++;
			flag = 1;
		}
		if ((str[i] == ';' || str[i] == '\0'))
		{
			count += (flag == 1) ? 1 : 0;
			flag = 0;
			i++;
		}
	}
	return (count);
}

static int		str_len(char *str, int i)
{
	int count;

	count = 0;
	while (str[i] != ';' && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

char	**split_commands(char *str)
{
	char	**res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if ((res = ft_memalloc(sizeof(char*) * (words(str) + 1))) == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ';' && str[i])
			i += 1;
		if (str[i])
		{ 
			k = 0;
			if ((res[j] = ft_memalloc(sizeof(char) * str_len(str, i) + 1)) == NULL)
				return (NULL);
			while (str[i] != ';' && str[i])
				res[j][k++] = str[i++];
			res[j++][k] = '\0';
		}
	}
	res[j] = NULL;
	return (res);
}
