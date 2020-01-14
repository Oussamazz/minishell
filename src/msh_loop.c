/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:52:44 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/14 17:22:42 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reg;

void	free_loop(char **str)
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void		ft_ctrlc(int sig)
{
	ft_putstr_color("\n$>", "\e[1;32m");
	reg = sig;
}

char		**parse_command(char **line, t_node **env)
{
	char *str;
	char *tmp;
	char **arr;

	str = NULL;
	arr = NULL;
	tmp = *line;
    (*env)->flag = false;
	if (line != NULL && (ft_is_there(tmp, '\'') || ft_is_there(tmp, '\"')))
	{
        (*env)->flag = true;
		str = modify(line);
		if (str == NULL)
			return (NULL);
		arr = split_commands(str);
		ft_strdel(&str);
		return (arr);
	}
	return (split_commands(tmp));
}

void	print_promt(char *cwd)
{
    if (cwd)
    {
        ft_putstr_color("[", "\033[1;34m");
	    ft_putstr_color(cwd, "\033[1;34m");
        ft_putstr_color("] ", "\033[1;34m");
	    ft_strcat(cwd, "/");
	    check_git(cwd);
	    ft_putstr_color(" » ", "\033[1;32m");
    }
    else
        ft_putstr_color(" » ", "\033[1;32m");
}

void    msh_loop(t_node **envp)
{
	t_split split;
    char    *tmp;

	ft_memset(&split, 0, sizeof(split));
	split.status = 1;
	//signal(SIGINT, ft_ctrlc);
	split.arr = NULL;
	split.line = NULL;
	while (split.status)
	{
        tmp = get_cwd(envp);
		print_promt(tmp);
		if (get_next_line(1, &split.line) == -1)
			return ;
		split.arr = parse_command(&split.line, envp);
		execute(&split, envp);
		if (ft_strcmp(split.line, "clear") == 0)
			clear_screen();
		free_loop(split.arr);
		ft_strdel(&split.line);
        ft_strdel(&tmp);
		split.status = 1;
	}
}
