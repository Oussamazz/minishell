/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:51:52 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/16 00:46:46 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		execute_direct(char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
			{
				if (execve(args[0], args, env) == -1)
					ft_putendl_fd("minishel : execution Failed!", 2);
				exit(0);
			}
			else
				ft_treeputstr(2, "minishell: permission denied: ", args[0], "\n");
		}
		else
		{
			ft_treeputstr(2, "minishell: Command not found: ", args[0], "\n");
			exit(0);
		}
	}
	else if (pid < 0)
		ft_putendl("minishell : Error forking.");
	else
		wait(NULL);
	return (1);
}

int			exec(char **args, t_node **head)
{
	int		i;
	char    **split_path;
	char    *path_env;
	char 	**env;
	char	*abs_path;

	split_path = NULL;
	if (!(env = to_arr(head)) || !(path_env = find_env("PATH", head)) || !(split_path = ft_strsplit(path_env, ':')))
		return (0);
	split_path = ft_strsplit(path_env, ':');
	i = 0;
	while (split_path[i] != NULL)
	{
		if (!(abs_path = ft_strjoin(ft_strcat(split_path[i], "/"), args[0])))
			return (0);
		ft_putendl(abs_path);
		if (args[0][0] == 47)
			stat = execute_direct(args, env);
		// else if (args[0][0] != 47 && abs_path)
		// {
		// 	ft_strdel(&args[0]);
		// 	args[0] = ft_strdup(abs_path);
		// 	execute_direct(args, env);
		// }
		ft_strdel(&abs_path);
		i++;
	}
	return (1);
}
