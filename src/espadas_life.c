/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espadas_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:03:22 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/08 05:46:28 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	espada_status(t_espada *e, char *str)
{
	long	t;

	t = now_ms() - (e->aizen->born_ms);
	pthread_mutex_lock(&e->aizen->order);
	printf("Espada %d  at %ld %s\n", e->id, t, str);
	pthread_mutex_unlock(&e->aizen->order);
}

static int	take_zanpakuto(t_espada *e)
{
	if (e->l_zanpakuto == e->r_zanpakuto)
	{
		pthread_mutex_lock(e->l_zanpakuto);
		espada_status(e, "has taken a fork");
		return (0);
	}
	if (e->id % 2 == 0)
	{
		pthread_mutex_lock(e->l_zanpakuto);
		espada_status(e, "has taken a fork");
		pthread_mutex_lock(e->r_zanpakuto);
		espada_status(e, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(e->r_zanpakuto);
		espada_status(e, "has taken a fork");
		pthread_mutex_lock(e->l_zanpakuto);
		espada_status(e, "has taken a fork");
	}
	return (1);
}

static void	drop_zanpakuto(t_espada *e)
{
	if (e->l_zanpakuto == e->r_zanpakuto)
	{
		pthread_mutex_unlock(e->l_zanpakuto);
		espada_status(e, "dropped a fork");
		return ;
	}
	pthread_mutex_unlock(e->l_zanpakuto);
	espada_status(e, "dropped a fork");
	pthread_mutex_unlock(e->r_zanpakuto);
	espada_status(e, "dropped a fork");
}

void	*routine(void *arg)
{
	t_espada	*e;

	e = (t_espada *)arg;
	espada_status(e, "is born");
	take_zanpakuto(e);
	drop_zanpakuto(e);
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
	aizen->born_ms = now_ms();
	while (i < aizen->arrancar)
	{
		espadas[i].id = i;
		espadas[i].aizen = aizen;
		espadas[i].l_zanpakuto = &aizen->zanpakuto[i];
		espadas[i].r_zanpakuto = &aizen->zanpakuto[(i + 1) % aizen->arrancar];
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
