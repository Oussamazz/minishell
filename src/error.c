/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:29:23 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/08 21:09:48 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void    error_command(char *str)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(str, 2);
}

char	*error_unmatched(int fd, char c, char **del)
{
	ft_putstr_fd("Unmatched ", 2);
	ft_putchar_fd(c, fd);
	ft_putstr_fd(".\n", 2);
	free(*del);
	return (NULL);
}

char	*error_msg(const char *str, int fd, char *ret)
{
	ft_putstr_fd(str, fd);
	return (ret);
}

int		check_firstchar(char *str)
{
	if (ft_isalpha(str[0]))
		return (1);
	ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	return (0);
}
