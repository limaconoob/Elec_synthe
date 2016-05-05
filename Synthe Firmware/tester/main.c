/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:54:04 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 21:21:46 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Midi.h"
#include "libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

# define ISONDE (ft_strcmp(argv[4], "C") && ft_strcmp(argv[4], "T") && ft_strcmp(argv[4], "D") && ft_strcmp(argv[4], "S"))

static int			ft_error(void)
{
	printf("ERROR: Usage: ./synthe (PRESETS) [octave] [demi-ton] ");
	printf("[centième] [C | T | D | S]\n");
	printf("C:Carrée, T:Triangle, D:Dent de scie, S:Sinusoïde\n");
	printf("Exemple : ./synthe 1 -3 40 C\n");
	return (-1);
}

int					main(int argc, char **argv)
{
	int				i;
	u32				tab_period[88];
	char			**av;

	if (argc != 5 || ISONDE)
		return(ft_error());

	tab_create(tab_period);
	if (!((av = (char**)malloc(sizeof(char*) * 5))))
	{
		ft_putendl("Error: Malloc can't allocate memory\n");
		return (-1);
	}
	av[4] = NULL;
	i = 0;
	while (argv[++i])
		av[i - 1] = ft_strdup(argv[i]);

	/*
	printf("\n----------> TABLEAU DE PERIODES <----------\n");
	i = 88;
	while (--i >= 0)
		printf("             note n°%d : %lu\n", i, tab_period[i]);
	printf("----------> TABLEAU DE PERIODES <----------\n\n");
	*/

	regprocess(tab_period, av);

	return(0);
}
