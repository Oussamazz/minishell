/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:17:43 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 17:32:25 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			cd_user(char *new_dir, t_node **head)
{
	struct stat st;
	char		cwd[PATH_MAX + 1];
	char		*tmp;

	if (new_dir && access(new_dir, F_OK) == 0)
	{
		stat(new_dir, &st);
		if (!S_ISDIR(st.st_mode))
		{
			ft_treeputstr(2, "cd: not a directory: ", new_dir, "\n");
			return ;
		}
		if (access(new_dir, X_OK) == 0)
		{
			tmp = get_cwd(head);
			gen_oldpwd(tmp, head);
			chdir(new_dir);
			ft_strdel(&tmp);
		}
		else
			ft_treeputstr(2, "cd: permission denied: ", new_dir, "\n");
	}
	else
		ft_treeputstr(2, "minishell: no such user or named directory: ",
			new_dir, "\n");
}

void			cd_home(char *path, t_node **head)
{
	char	*new_dir;
	char	*home;

	home = find_env("HOME", head);
	if ((path[0] == '~' && path[1] == '\0') || !ft_strcmp(path, "cd"))
		cd_root(home, head);
	else if (path[0] == '~' && path[1] == 47)
	{
		new_dir = ft_strjoin(home, &path[1]);
		cd_root(new_dir, head);
		ft_strdel(&new_dir);
	}
	else if (path[0] == '~' && path[1] != 47)
	{
		new_dir = ft_strjoin("/Users/", path + 1);
		cd_user(new_dir, head);
		ft_strdel(&new_dir);
	}
	else if (path[0] == '$')
	{
		new_dir = env_var_rep(head, path);
		cd_root(new_dir, head);
		ft_strdel(&new_dir);
	}
	ft_strdel(&home);
}

void			gen_pwd(char *new_path, t_node **head)
{
	char	*str;

	if (new_path == NULL)
		return ;
	str = ft_strjoin("PWD=", new_path);
	if (is_exist(head, str) == 1)
		ft_repenv(head, str);
	else
		push(head, str);
	ft_strdel(&str);
}
