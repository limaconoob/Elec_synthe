/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_period.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 21:09:40 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 22:43:30 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Midi.h"
#include "libft.h"
#include <stdio.h>

void         print_period(u32 period, char *onde)
{
	if (!ft_strcmp(onde, "C"))
	{
		printf("Tension ,^,\n");
		printf("  0xFFFF_|        ,________,        ,____\n");
		printf("         |        |        |        |\n");
		printf("         |        |        |        |\n");
		printf("  0x8000_|        |        |        |\n");
		printf("---------+--------|--------|--------|-----> \n");
		printf("  0x7FFF_|        |        |        | Temps(μs/20)\n");
		printf("         |        |        |        |\n");
		printf("         |        |        |        |\n");
		printf("  0x0000_|________|        |________|\n");
		printf("                %lu    %lu    %lu\n", period, period * 2, period * 3);
	}
	else if (!ft_strcmp(onde, "D"))
	{
		printf("Tension ,^,\n");
		printf("  0xFFFF_|        ,        ,        ,\n");
		printf("         |       /|       /|       /|\n");
		printf("         |      / |      / |      / |\n");
		printf("  0x8000_|     /  |     /  |     /  |\n");
		printf("---------+----/---|----/---|----/---|---> \n");
		printf("  0x7FFF_|   /    |   /    |   /    | Temps(μs/20)\n");
		printf("         |  /     |  /     |  /     |\n");
		printf("         | /      | /      | /      |\n");
		printf("  0x0000_|/       |/       |/       |\n");
		printf("                %lu    %lu    %lu\n", period, period * 2, period * 3);
	}
	else if (!ft_strcmp(onde, "T"))
	{
		printf("Tension ,^,\n");
		printf("  0xFFFF_|            ,                ,\n");
		printf("         |           / \\              /\n");
		printf("         |          /   \\            /\n");
		printf("  0x8000_|         /     \\          /\n");
		printf("---------+--------/-------\\--------/-----> \n");
		printf("  0x7FFF_|\\      /         \\      / Temps(μs/20)\n");
		printf("         | \\    /           \\    /  \n");
		printf("         |  \\  /             \\  /   \n");
		printf("  0x0000_|   \\/               \\/    \n");
		printf("           %lu    %lu    %lu\n", period, period * 2, period * 3);
	}
	else if (!ft_strcmp(onde, "S"))
	{
		printf("Tension ,^,\n");
		printf("  0xFFFF_|             ,-,               ,\n");
		printf("         |            l   l             l\n");
		printf("         |           l     l           l\n");
		printf("  0x8000_|          l       l         l \n");
		printf("---------+l---------l-------l---------l---> \n");
		printf("  0x7FFF_|l         l       l         l Temps(μs/20)\n");
		printf("         | l       l         l       l  \n");
		printf("         |  l     l           l     l   \n");
		printf("  0x0000_|   \\,_,/             \\,_,/    \n");
		printf("            %lu     %lu     %lu\n", period, period * 2, period * 3);
	}
}
