/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:03:07 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 18:23:15 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include "error.h"
# define NO_ZERO(x) x == 0 ? 1 : x
# define DELIM "\t\n "
# define QUOTES "\'\""

typedef struct		s_node
{
	bool			flag;
	char			*data;
	struct s_node	*next;
}					t_node;

typedef struct		s_quote
{
	int			i;
	int			o;
	int			close_q;
	int			open_q;
	bool		open_q_err;
	char		quote;
}					t_quote;
typedef struct		s_split
{
	int		status;
	char	**arr;
	char	**args;
	char	*line;
}					t_split;
void				blank_value_replace(char **arr);
char				**msh_split_line(char *line);
char				**split_commands(char *str);
char				*modify(char **arr);
void				msh_loop(t_node **envp);
void				execute(t_split *split, t_node **envp);
void				ft_ctrlc(int sig);
int					msh_execute(char **args, t_node **envp);
void				exec(char **args, t_node **head);
void				msh_echo(char **args, t_node **envp);
void				ft_setenv(t_node **head, char **args);
void				ft_unsetenv(t_node **head, char **str, int len);
void				ft_cd(char **args, t_node **head);
void				stock_env(char **env, t_node **node);
char				*find_env(char *str, t_node **envp);
void				append(t_node **head, char *data);
void				delete_node(t_node **head, char *str);
void				push(t_node **head, char *data);
void				ft_putstr_color(char const *s, char *str);
void				clear_screen(void);
void				print_list(t_node **head);
void				git(char *tmp);
void				error_command(char *str);
int					is_exist(t_node **head, char *str);
int					is_str_exist(t_node **head, char *str);
int					tablen(char **arr);
void				free_loop(char **str);
void				check_git(char *path);
char				*get_cwd(t_node **head);
void				cd_home(char *path, t_node **head);
void				cd_user(char *new_dir, t_node **head);
void				cd_root(char *new_dir, t_node **head);
void				ft_repenv(t_node **head, char *str);
void				gen_oldpwd(char *cwd, t_node **head);
char				*env_var_rep(t_node **head, char *str);
char				**to_arr(t_node **head);
void				gen_pwd(char *new_path, t_node **head);
int					check_str(char *str);
#endif
