/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:46:45 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/13 18:18:47 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_char(const char *str, char c)
{
	size_t	len;

	if (str)
	{
		len = 0;
		while (str[len] && str[len] != c)
			len++;
		return (len);
	}
	return (-1);
}
