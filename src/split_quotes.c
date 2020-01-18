/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 12:35:13 by oelazzou          #+#    #+#             */
/*   Updated: 2020/01/18 18:23:18 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

bool		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

int			second_quote(char *str, int index, char c)
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
	if (((((quotes)->open_q) > 0 || (quotes)->open_q_err) &&
		(quotes)->quote == str[i]))
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

void		blank_val(char **str, int *o, char c)
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

char		*modify(char **arr)
{
	char	*str;
	char	*tmp;
	t_quote	quotes;

	tmp = ft_strdup(*arr);
	if (!(str = ft_memalloc(sizeof(char) * ft_strlen(tmp))))
		return (NULL);
	ft_memset(&quotes, 0, sizeof(t_quote));
	quotes.i = -1;
	quotes.o = 0;
	while (tmp[++quotes.i] != '\0')
	{
		quotes_index(quotes.i, &tmp, &quotes);
		if ((tmp[quotes.i] == ';' || ft_is_there(DELIM, tmp[quotes.i])) &&
			(quotes.open_q || quotes.open_q_err))
			blank_val(&str, &quotes.o, tmp[quotes.i]);
		else if ((quotes.i != quotes.close_q &&
			quotes.i != quotes.open_q) || (quotes.i == 0 &&
				!is_quote(tmp[quotes.i])))
			str[quotes.o++] = tmp[quotes.i];
	}
	free(tmp);
	if (!quotes.close_q && (quotes.open_q_err || quotes.open_q))
		return (error_unmatched(2, quotes.quote, &str));
	return (str);
}
