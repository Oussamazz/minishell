/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:51:52 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 17:23:51 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_direct(char *path, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				if (execve(path, args, env) == -1)
					ft_putendl_fd("minishel : execution Failed!", 2);
				exit(0);
			}
			ft_treeputstr(2, "minishell: permission denied: ", args[0], "\n");
			exit(0);
		}
		else
			ft_treeputstr(2, "minishell: Command not found: ", args[0], "\n");
		exit(0);
	}
	else if (pid < 0)
		ft_putendl("minishell : Error forking.");
	else
		wait(NULL);
}

char			*ft_ret_freetab(char *str, char **tab, char *fre, char *fre2)
{
	free_loop(tab);
	free(fre);
	free(fre2);
	return (str);
}

static char		*ft_strdup_free(char *str, char **str2, char **arr)
{
	free_loop(arr);
	ft_strdel(str2);
	return (str);
}

char			*find_right_path(char **args, t_node **head)
{
	int		i;
	char	**split_path;
	char	*path_env;
	char	*abs_path;

	split_path = NULL;
	path_env = find_env("PATH", head);
	if (!(split_path = ft_strsplit(path_env, ':')))
		return (ft_strdup_free(ft_strdup(args[0]), &path_env, split_path));
	i = -1;
	while (split_path[++i] != NULL)
	{
		if (!(abs_path = ft_strjoin(ft_strcat(split_path[i], "/"), args[0])))
			break ;
		if (args[0][0] != '.' && args[0][0] != 47)
		{
			if (access(abs_path, F_OK) == 0)
				return (ft_ret_freetab(abs_path, split_path, path_env, NULL));
		}
		else if (access(args[0], F_OK) == 0)
			return (ft_ret_freetab(ft_strdup(args[0]),
			split_path, path_env, abs_path));
			ft_strdel(&abs_path);
	}
	return (ft_ret_freetab(NULL, split_path, abs_path, path_env));
}

void			exec(char **args, t_node **head)
{
	char	*right_path;
	char	**env;
	char	*tmp;

	right_path = NULL;
	tmp = NULL;
	if (args[0][0] == '$')
	{
		if (!(tmp = find_env(&args[0][1], head)))
			return (ft_treeputstr(2, &args[0][1],
				": Undefined variable.", "\n"));
			right_path = find_right_path(&tmp, head);
	}
	else if (!(right_path = find_right_path(args, head)))
		return (ft_treeputstr(2, "minishell: Command not found: ",
			args[0], "\n"));
		env = to_arr(head);
	if (env)
	{
		execute_direct(right_path, args, env);
		ft_strdel(&right_path);
		ft_strdel(&tmp);
		free_loop(env);
	}
}
