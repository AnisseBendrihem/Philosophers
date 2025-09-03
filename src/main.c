/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:51 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/03 04:51:28 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_null_agora(t_agora *god)
{
	god->philosophers = 0;
	god->time_to_die = 0;
	god->time_to_eat = 0;
	god->time_to_sleep = 0;
	god->meals = 0;
}

int	main(int ac, char **av)
{
	t_agora	god;

	init_null_agora(&god);
	if (mother_parsing(&god, ac, av))
	{
		printf("Initialisation\n");
		printf("nombre de philo %d\n", god.philosophers);
		printf("temps pour mourir %d\n", god.time_to_die);
		printf("temps pour manger %d\n", god.time_to_eat);
		printf("temps pour dormir %d\n", god.time_to_sleep);
		if (ac == 6)
			printf("nombre de repas (optionnel)%d\n", god.meals);
	}
	return (0);
}
