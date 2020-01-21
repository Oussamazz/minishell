/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:52:44 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/21 18:12:16 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_reg;

void		free_loop(char **str)
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i] != NULL)
		{
			ft_strdel(&str[i]);
			i++;
		}
		free(str);
	}
}

char		**parse_command(char **line, t_node **env)
{
	char	*str;
	char	*tmp;
	char	**arr;

	str = NULL;
	arr = NULL;
	if (*env == NULL)
		push(env, "");
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

void		print_promt(char *cwd)
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

void		ft_ctrlc(int sig)
{
	char buf[PATH_MAX + 1];

	wait(NULL);
	ft_putchar('\n');
	if (g_reg != 1)
		print_promt(getcwd(buf, sizeof(buf)));
	g_reg = -1;
}

void		msh_loop(t_node **envp)
{
	t_split	split;
	char	*tmp;

	ft_memset(&split, 0, sizeof(split));
	split.status = 1;
	signal(SIGINT, ft_ctrlc);
	split.arr = NULL;
	split.line = NULL;
	while (split.status > 0)
	{
		tmp = get_cwd();
		g_reg = 0;
		if (g_reg == 0)
			print_promt(tmp);
		free(tmp);
		if ((split.status = get_next_line(1, &split.line)) == -1)
			return ;
		if (split.status == 0)
			return (ft_treeputstr(2, "\nStopped: Line reached EOF!\n", "", ""));
		split.arr = parse_command(&split.line, envp);
		g_reg = 1;
		execute(&split, envp);
		free_loop(split.arr);
		ft_strdel(&split.line);
	}
}
