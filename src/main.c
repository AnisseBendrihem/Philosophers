/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:51 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/07 04:11:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	empty_mundo(t_hueco_mundo *aizen)
{
	aizen->arrancar = 0;
	aizen->time_to_die = 0;
	aizen->time_to_eat = 0;
	aizen->time_to_sleep = 0;
	aizen->soul = 0;
}

void	*routine(void *arg)
{
	t_espada	*e;

	e = (t_espada *)arg;
	pthread_mutex_lock(&e->aizen->order);
	printf("Espada %d is ready\n", e->id);
	pthread_mutex_unlock(&e->aizen->order);
	return (NULL);
}

int	espada_born(t_hueco_mundo *aizen)
{
	int			i;
	t_espada	*espadas;

	pthread_mutex_init(&aizen->order, NULL);
	espadas = malloc(sizeof(*espadas) * aizen->arrancar);
	if (!espadas)
		return (1);
	i = 0;
	while (i < aizen->arrancar)
	{
		espadas[i].id = i;
		espadas[i].aizen = aizen;
		if (pthread_create(&espadas[i].thread, NULL, routine, &espadas[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < aizen->arrancar)
	{
		if (pthread_join(espadas[i].thread, NULL))
			return (2);
		i++;
	}
	pthread_mutex_destroy(&aizen->order);
	free(espadas);
	return (0);
}

int	main(int ac, char **av)
{
	t_hueco_mundo	aizen;

	empty_mundo(&aizen);
	if (mother_parsing(&aizen, ac, av))
		printf("Initialisation\n");
	espada_born(&aizen);
	return (0);
}
