/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:29:32 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 18:13:41 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void		ft_repenv(t_node **head, char *str)
{
	size_t str_len;
	t_node *tmp;

	str_len = ft_strlen_char(str, '=') + 1;
	tmp = *head;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->data, str, str_len))
		{
			ft_strdel(&(tmp->data));
			tmp->data = ft_strdup(str);
			return ;
		}
		tmp = tmp->next;
	}
}

char		*env_var_rep(t_node **head, char *str)
{
	char	*env;

	env = NULL;
	while (*str == '$')
		str++;
	if (!(env = find_env(str, head)))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" Undefined variable.", 2);
		return (NULL);
	}
	return (env);
}

static char	*get_envstr(t_node **head, char **args, int *tablen)
{
	char	*name;
	char	*tmp;

	if (*tablen > 3)
		return (error_msg(0, 2, NULL));
	if (!ft_isalpha(args[1][0]))
		return (error_msg(1, 2, NULL));
	if (!check_str(args[1]))
		return (error_msg(2, 2, NULL));
	name = ft_strcat(args[1], "=");
	if (args[2] != NULL)
	{
		if (args[2][0] == '$')
		{
			tmp = args[2];
			args[2] = env_var_rep(head, args[2]);
			ft_strdel(&tmp);
		}
		return (ft_strjoin(name, args[2]));
	}
	return (ft_strdup(name));
}

void		ft_setenv(t_node **head, char **args)
{
	int		i;
	char	*add_env;

	add_env = NULL;
	i = tablen(args);
	if (i == 1)
	{
		print_list(head);
		return ;
	}
	if (i >= 2)
	{
		add_env = get_envstr(head, args, &i);
		if (!add_env)
			return ;
		if (!(is_exist(head, add_env)))
			append(head, add_env);
		else if (is_exist(head, add_env))
			ft_repenv(head, add_env);
		ft_strdel(&add_env);
	}
}

void		ft_unsetenv(t_node **head, char **str, int len)
{
	int		i;
	size_t	len_data;
	t_node	*tmp;

	tmp = *head;
	i = 1;
	while (i < len)
	{
		while (tmp != NULL)
		{
			len_data = ft_strlen_char(tmp->data, '=');
			if (len_data != 0 && !ft_strncmp(tmp->data, str[i], len_data))
				delete_node(head, str[i]);
			tmp = tmp->next;
		}
		tmp = *head;
		i++;
	}
	return ;
}
