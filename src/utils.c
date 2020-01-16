/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:53:25 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/16 20:47:48 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gen_oldpwd(char *cwd, t_node **head)
{
	bool    flag;
	char    *str;

	flag = false;
	if (cwd == NULL)
	{
		flag = true;
		cwd = find_env("PWD", head);
	}
	if (cwd == NULL)
		return ;
	str = ft_strjoin("OLDPWD=", cwd);
	if (is_exist(head, str) == 1)
		ft_repenv(head, str);
	else
		push(head, str);
	if (flag)
		ft_strdel(&cwd);
	ft_strdel(&str);
}

char	*get_cwd(t_node ** head)
{
	char *buff;

	buff = NULL;
	buff = ft_strnew(PATH_MAX);
	if (!buff)
		return (NULL);
	buff = getcwd(buff, PATH_MAX);
	return (buff);
}

void	check_git(char *path)
{
	DIR             *dir;
	char            *head_file;
	char            *tmp;
	int             fd_git;
	struct dirent   *dp;

	dir = opendir(path);
	if (!dir)
		return ;
	while ((dp = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(dp->d_name, ".git"))
		{
			if ((fd_git = open(ft_strcat(path, ".git/HEAD"), O_RDONLY)) == -1)
				return ;
			get_next_line(fd_git, &head_file);
			if (head_file && (tmp = ft_strrchr(head_file, '/') + 1))
				git(tmp);
			ft_strdel(&head_file);
			close(fd_git);
			closedir(dir);
			return ;
		}
	}
	closedir(dir);
}

static size_t  list_size(t_node **head)
{
	size_t count;
	t_node *cur;

	cur = *head;
	count = 0;
	while (cur != NULL)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char    **to_arr(t_node **head)
{
	size_t size;
	int	i;
	char **arr;
	t_node *cur;

	size = list_size(head);
	if (!(arr = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	cur = *head;
	i = 0;
	while (cur != NULL)
	{
		arr[i] = ft_strdup(cur->data);
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}
