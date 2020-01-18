/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeputstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:12:39 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/11 19:17:55 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_treeputstr(int fd, const char *str1, const char *str2,
	const char *str3)
{
	if (str1 && str2 && str3)
	{
		ft_putstr_fd(str1, fd);
		ft_putstr_fd(str2, fd);
		ft_putstr_fd(str3, fd);
	}
	return ;
}
