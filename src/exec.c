/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:51:52 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/16 15:21:06 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_direct(char *path, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (access(path, X_OK) == 0)
		{
			if (execve(path, args, env) == -1)
				ft_putendl_fd("minishel : execution Failed!", 2);
			exit(0);
		}
		else
			ft_treeputstr(2, "minishell: permission denied: ", args[0], "\n");
		exit(0);
	}
	else if (pid < 0)
		ft_putendl("minishell : Error forking.");
	else
		wait(NULL);
	return ;
}

static char		*find_right_path(char **args, t_node **head)
{
	int		i;
	char    **split_path;
	char    *path_env;
	char	*abs_path;

	split_path = NULL;
	if (!(path_env = find_env("PATH", head)) || !(split_path = ft_strsplit(path_env, ':')))
		return (0);
	i = 0;
	while (split_path[i] != NULL)
	{
		if (!(abs_path = ft_strjoin(ft_strcat(split_path[i], "/"), args[0])))
			return (NULL);
		if (args[0][0] != '.' && args[0][0] != 47)
		{
			if (access(abs_path, F_OK) == 0)
				return (ft_strdup(abs_path));	
		}
		else if (access(args[0], F_OK) == 0)
			return (ft_strdup(args[0]));
		i++;
	}
	return (NULL);
}

void	exec(char **args, t_node **head)
{
	char *right_path;
	char **env;

	right_path = NULL;
	if (!(right_path = find_right_path(args, head)))
		return (ft_treeputstr(2, "minishell: Command not found: ", args[0], "\n"));
	if (!(env = to_arr(head)))
		return ;
	execute_direct(right_path, args, env);
	free_loop(env);
	ft_strdel(&right_path);
}