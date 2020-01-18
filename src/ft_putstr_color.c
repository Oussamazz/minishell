/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:20:18 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 17:27:39 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_color(char const *s, char *str)
{
	ft_putstr(str);
	if (s)
	{
		while (*s)
			ft_putchar(*s++);
	}
	ft_putstr("\e[0m");
}
