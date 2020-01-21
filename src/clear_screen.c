/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:07:11 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/21 18:48:23 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_screen(void)
{
	const char *clear;

	clear = "\e[1;1H\e[2J";
	ft_putstr_fd(clear, 1);
}
