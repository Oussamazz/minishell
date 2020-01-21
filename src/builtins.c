/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:01:32 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/21 19:23:02 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*find_env(char *str, t_node **envp)
{
	t_node	*cur;
	char	*tmp;

	cur = *envp;
	if (str && *str)
	{
		while (cur)
		{
			if (!ft_strncmp(str, cur->data, ft_strlen_char(cur->data, '='))
				&& ft_strlen_char(str, '$') == ft_strlen_char(cur->data, '='))
			{
				if (!(tmp = ft_strchr(cur->data, '=') + 1) || tmp[0] == '\0')
					return (NULL);
				return (ft_strdup(tmp));
			}
			cur = cur->next;
		}
	}
	return (NULL);
}

static int	put_env(char *str, t_node **envp)
{
	size_t	strlen;
	int		count;
	char	*env;

	count = 0;
	strlen = 0;
	while (*str == '$')
	{
		count++;
		str++;
	}
	strlen += ft_strlen_char(str, '$');
	env = find_env(str, envp);
	if (env != NULL)
		ft_putstr(env);
	else
	{
		ft_putstr_len_fd(str, strlen, 2);
		ft_putstr_fd(": Undefined variable.\n", 2);
		return (-4096);
	}
	ft_strdel(&env);
	return (strlen + count);
}

static int	path_home(char *str, t_node **envp)
{
	int		i;
	char	*env;

	i = 0;
	if (!(env = find_env("HOME", envp)))
		return (0);
	if (str[0] != '\0' && str[0] != 47)
	{
		if (str[0] == '$')
		{
			ft_putstr(env);
			ft_strdel(&env);
			return (put_env(str + 1, envp) + 1);
		}
		ft_treeputstr(1, "Unknown user: ", str, ".");
		ft_strdel(&env);
		return (ft_strlen(str));
	}
	ft_putstr(env);
	ft_strdel(&env);
	return (0);
}

static int	msh_echo_continue(char **args, t_node **head, int i, int *j)
{
	if (args[i][*j] == '~' && !(*head)->flag)
		*j += path_home(&args[i][*j + 1], head);
	else if (args[i][*j] == '$' && args[i][*j + 1] != '\0')
		*j += put_env(&args[i][*j + 1], head);
	else
		ft_putchar(args[i][*j]);
	if (*j <= -1)
		return (-1);
	return (1);
}

void		msh_echo(char **args, t_node **envp)
{
	int		i;
	int		j;
	bool	flag;

	i = 1;
	flag = 0;
	if (args[1] != NULL && !strncmp(args[1], "-n", ft_strlen(args[1])))
	{
		i = 2;
		flag = 1;
	}
	while (args[i] != NULL)
	{
		j = -1;
		while (args[i][++j] && j < ft_strlen(args[i]))
			if (msh_echo_continue(args, envp, i, &j) <= -1)
				return ;
		if (args[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	if (!flag)
		ft_putchar('\n');
}
