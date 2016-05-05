/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 11:35:19 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 22:50:06 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Midi.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdio.h>

static char			**regcommand_line(void)
{
	char			buf[1];
	char			*line;

	line = NULL;
	while (read(0, buf, 1) && buf[0] != '\n')
		line = ft_concat(line, buf, 1);
	return (ft_splitspaces(line));
}

static void			do_exec(char **av, u32 *tab_period, char **pre)
{
	int				i;
	int				note;
	int				cent;
	u32				period;

	if (!ft_strcmp(av[0], "help"))
	{
		printf("    -----> HELP <-----\n");
		printf(" $> help      // Display this message\n");
		printf(" $> [0-87]    // Display info about this midi note\n");
		printf(" $> preset [octave] [demi-ton] [centième] [C | T | D | S]");
		printf(" // Change presets\n                    ");
		printf(" // C=Carrée, T=Triangulaire, D=Dent de scie, S=Sinusoïdale\n");
		printf(" $> exit      // Exit program\n");
		return ;
	}
	i = 0;
	while (av[0][i] && av[0][i] >= '0' && av[0][i] <= '9')
		i++;
	if (av[0][i] && (av[0][i] < '0' || av[0][i] > '9'))
	{
		printf("    -----> ERROR <-----\n");
		printf("For help about usages: $> help\n");
	}
	else
	{
		note = atoi(av[0]);
		if (note > 87 || note < 0)
		{
			printf("    -----> ERROR <-----\n");
			printf("For help about usages: $> help\n");
			return ;
		}
		printf("Note: %d, Period: %lu\n", note, tab_period[note]);
		printf("Presets: octave:%s demi-ton:%s centième:%s onde:%s\n", pre[0], pre[1], pre[2], pre[3]);
		note += atoi(pre[0]) * 12;
		note += atoi(pre[1]);
		cent = 0;
		printf("Note After Presets: %d", note);
		if (note >= 0 && note <= 87)
		{
			if (note >= 0 && note < 87)
			{
				cent = tab_period[note] - tab_period[note + 1];
				cent /= 100;
				cent *= atoi(pre[2]);
				period = tab_period[note] + cent;
			}
			else
			{
				cent = tab_period[note] - tab_period[note - 1];
				cent /= 100;
				cent *= atoi(pre[2]);
				period = tab_period[note] - cent;
			}
			printf(", New Period: %lu\n", period);
			
			print_period(period, pre[3]);
		}
		else
			printf("\nError: Invalid presets for this note.\n");
	}
}

void				regprocess(u32 *tab_period, char **presets)
{
	pid_t			father;
	static char		**av;
	char			*line;
	static int		first_log = 0;
	int				i;

	while (PROCESS)
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			if (first_log == 1)
				printf("\n");
			ft_putstr("$> ");
			av = regcommand_line();
			if (av && !ft_strcmp(av[0], "exit"))
				return ;
			else if (!ft_strcmp(av[0], "preset") && tab_size(av) == 5)
			{
				i = -1;
				printf("New Presets: ");
				while (++i < 4)
				{
					free(presets[i]);
					presets[i] = av[i + 1];
					printf("%s ", presets[i]);
				}
				printf("\n");
			}
			first_log = 1;
		}
		if (father == 0)
		{
			if (av && first_log && tab_size(av) == 1)
				do_exec(av, tab_period, presets);
			else if (av && first_log && ft_strcmp(av[0], "preset"))
			{
				printf("    -----> ERROR <-----\n");
				printf("For help about usages: $> help\n");
			}
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
}
