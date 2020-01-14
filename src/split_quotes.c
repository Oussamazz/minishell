/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 12:35:13 by oelazzou          #+#    #+#             */
/*   Updated: 2019/12/28 16:05:05 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

int		second_quote(char *str, int index, char c)
{
	if (str)
	{
		while (str[index] != '\0')
		{
			if (str[index] == c)
				return (index);
			index++;
		}
		return (0);
	}
	return (0);
}

void		quotes_index(int i, char **tmp, t_quote *quotes)
{
	char *str;

	str = *tmp;
	if (((((quotes)->open_q) > 0 || (quotes)->open_q_err) && (quotes)->quote == str[i]))
	{
		(quotes)->open_q = 0;
		(quotes)->open_q_err = 0;
		return ;
	}
	if (is_quote(str[i]) && (quotes)->open_q == 0 && !(quotes)->open_q_err)
	{
		if (i == 0)
			(quotes)->open_q_err = 1;
		else	
			(quotes)->open_q = i;
		(quotes)->close_q = second_quote(str, i + 1, str[i]);
		(quotes)->quote = str[i];
		return ;
	}
	else if (is_quote(str[i]) && (i == (quotes)->close_q))
					(quotes)->open_q = 0;
}

void	blank_val(char **str, int *o, char c)
{
	char *tmp;

	tmp = *str;
	if (c == ' ')
		tmp[(*o)] = -1;
	else if (c == '\t')
		tmp[(*o)] = -2;
	else if (c == ';')
		tmp[(*o)] = -3;
	(*o) = (*o) + 1;
}


// static void	init_values(t_quote *q)
// {
// 	(q)->close_q = 0;
// 	(q)->open_q = 0;
// 	(q)->open_q_err = 0;
// 	(q)->quote = 0;
// }

char	*modify(char **arr)
{
	int		i;
	char	*str;
	char 	*tmp;
	t_quote quotes;
	int o;

	tmp = ft_strdup(*arr);
	if (!(str = ft_memalloc(sizeof(char) * ft_strlen(tmp))))
		return (NULL);
	ft_memset(&quotes, 0, sizeof(t_quote));
	i = -1;
	o = 0;
	while (tmp[++i] != '\0')
	{
		quotes_index(i, &tmp, &quotes);
		if ((tmp[i] == ';' || ft_is_there(DELIM, tmp[i])) && (quotes.open_q || quotes.open_q_err)) //checking whitespaces between " " and ;
			blank_val(&str, &o, tmp[i]);
		else if ((i != quotes.close_q && i != quotes.open_q) || (i == 0 && !is_quote(tmp[i])))
			str[o++] = tmp[i];
	}
	free(tmp);
	if (!quotes.close_q && (quotes.open_q_err || quotes.open_q))
		return (error_unmatched(2, quotes.quote, &str));
	return (str);
}
		//printf("open: %d | close: %d | err : %d | i = %d | character %c : | quote: %c\n", quotes.open_q, quotes.close_q,quotes.open_q_err, i,tmp[i], quotes.quote);	
