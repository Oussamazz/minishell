/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:33:47 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/11 19:19:23 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_len_fd(const char *str, size_t len, int fd)
{
	int i;

	i = 0;
	while (str[i] && len)
	{
		ft_putchar_fd(str[i], fd);
		len--;
		i++;
	}
	return ;
}
