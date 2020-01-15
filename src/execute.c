/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 10:17:19 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/15 21:31:23 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		blank_value_replace(char **arr)
{
	int i;
	int j;

	i = -1;
	if (arr)
	{
		while (arr[++i] != NULL)
		{
			j = -1;
			while (arr[i][++j] != '\0')
			{
				if (arr[i][j] < 0)
				{
					if (arr[i][j] == -1)
						arr[i][j] = ' ';
					if (arr[i][j] == -2)
						arr[i][j] = '\t';
					if (arr[i][j] == -3)
						arr[i][j] = ';';
				}
			}
		}
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}

void		execute(t_split *split, t_node **envp)
{
	int i;

	if (split->arr)
	{
		i = -1;
		while (split->arr[++i] != NULL)
		{
			split->args = msh_split_line(split->arr[i]);
			blank_value_replace(split->args);
			msh_execute(split->args, envp);
			free_loop(split->args);
		}
	}
}



void		msh_execute(char **args, t_node **envp)
{
    if (args[0] == NULL || !args[0][0])
        return ;
	if (!ft_strcmp(args[0], "echo"))
		msh_echo(args, envp);
	else if (!ft_strcmp(args[0], "setenv"))
		ft_setenv(envp, args);
	else if (!ft_strcmp(args[0], "unsetenv"))
		ft_unsetenv(envp, args, tablen(args));
	else if (!ft_strcmp(args[0], "env"))
		ft_setenv(envp, args);
	else if (!ft_strcmp(args[0], "exit"))
		exit(EXIT_SUCCESS);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args, envp);
	else if (ft_strcmp(args[0], "clear") == 0)
			clear_screen();
    else
		exec(args, envp);
}
