/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treestrdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:53:06 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/13 16:57:26 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_treestrdel(char **str1, char **str2, char **str3)
{
	ft_strdel(str1);
	ft_strdel(str2);
	ft_strdel(str3);
}
