/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 08:15:46 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 18:54:55 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Midi.h"
#include "libft.h"
#include <stdlib.h>

static int			ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int			ft_count(char *str)
{
	int				i;

	i = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str)
		{
			while (*str && !ft_isspace(*str))
				str++;
			i++;
		}
	}
	return (i);
}

char			**ft_splitspaces(char *str)
{
	int			count;
	char		**tab;
	int			i;

	if (!str)
		return (NULL);
	count = ft_count(str);
	if (!((tab = (char**)malloc(sizeof(char*) * (count + 1)))))
		;
	tab[count] = NULL;
	count = 0;
	while (*str)
	{
		i = 0;
		while (ft_isspace(*str))
			str++;
		if (*str)
		{
			while (str[i] && !ft_isspace(str[i]))
				i++;
			tab[count++] = ft_strsub(str, 0, i);
			str += i;
		}
		else
			break ;
	}
	return (tab);
}
