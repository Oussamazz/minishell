/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:51:42 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 17:08:41 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		cd_smp(char *cwd, char *path, char *new_dir, t_node **head)
{
	struct stat	st;
	char		*tmp;

	stat(new_dir, &st);
	if (!S_ISDIR(st.st_mode))
	{
		ft_treeputstr(2, "cd: not a directory: ", path, "\n");
		return ;
	}
	if (access(new_dir, X_OK) == 0)
	{
		gen_oldpwd(cwd, head);
		chdir(new_dir);
		gen_pwd((tmp = get_cwd(head)), head);
		ft_strdel(&tmp);
	}
	else
		ft_treeputstr(2, "cd: permission denied: ", path, "\n");
}

static void		cd_simple(char *path, t_node **head)
{
	char *new_dir;
	char *cwd;

	new_dir = NULL;
	if ((cwd = get_cwd(head)))
	{
		ft_strcat(cwd, "/");
		new_dir = ft_strjoin(cwd, path);
	}
	else if (chdir(path) == 0)
	{
		gen_oldpwd((cwd = find_env("PWD", head)), head);
		ft_strdel(&cwd);
		return ;
	}
	if (new_dir && access(new_dir, F_OK) == 0)
		cd_smp(cwd, path, new_dir, head);
	else
		ft_treeputstr(2, "cd: no such file or directory: ", path, "\n");
	ft_treestrdel(&new_dir, &cwd, NULL);
}

void			cd_root(char *new_dir, t_node **head)
{
	struct stat st;
	char		cwd[PATH_MAX + 1];
	char		*tmp;
	char		*tmp2;

	if (new_dir && access(new_dir, F_OK) == 0)
	{
		stat(new_dir, &st);
		if (!S_ISDIR(st.st_mode))
			return (ft_treeputstr(2, "cd: not a directory: ", new_dir, "\n"));
		if (access(new_dir, X_OK) == 0)
		{
			gen_oldpwd((tmp = get_cwd(head)), head);
			chdir(new_dir);
			gen_pwd((tmp2 = get_cwd(head)), head);
			ft_treestrdel(&tmp, &tmp2, NULL);
		}
		else
			ft_treeputstr(2, "cd: permission denied: ", new_dir, "\n");
	}
	else
		ft_treeputstr(2, "cd: no such file or directory: ", new_dir, "\n");
}

static void		cd_back(t_node **head)
{
	char *path;

	path = find_env("OLDPWD", head);
	if (path != NULL)
	{
		cd_root(path, head);
		ft_strdel(&path);
	}
	return ;
}

void			ft_cd(char **args, t_node **head)
{
	size_t		args_len;
	char		buff[PATH_MAX + 1];

	if ((args_len = tablen(args)) > 2)
		return (ft_putendl_fd("cd: Too many arguments.", 2));
	else if (args_len == 1)
		return (cd_home(args[0], head));
	ft_strcpy(buff, args[1]);
	if (args[1][0] == '~' || args[1][0] == '$')
		cd_home(buff, head);
	else if (args[1][0] == '-' && args[1][1] == '\0')
		cd_back(head);
	else if (args[1][0] == 47)
		cd_root(buff, head);
	else
		cd_simple(buff, head);
}
