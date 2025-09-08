/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espadas_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:03:22 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/08 15:39:05 by abendrih         ###   ########.fr       */
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
		return ;
	}
	pthread_mutex_unlock(e->l_zanpakuto);
	pthread_mutex_unlock(e->r_zanpakuto);
}

void	*routine(void *arg)
{
	t_espada	*e;

	e = (t_espada *)arg;
	while (e->alive == true)
	{
		take_zanpakuto(e);
		drop_zanpakuto(e);
		if ((now_ms() - e->last_meal_ms) < e->aizen->time_to_die)
		{
			espada_status(e, "\033[1;35mis eating\033[0m"); // magenta vif
			usleep(e->aizen->time_to_eat);
		}
		else
		{
			e->alive = false;
			espada_status(e, "\033[1;31mis dead\033[0m"); // rouge vif
			break ;
		}
		espada_status(e, "\033[1;36mis sleeping\033[0m"); // cyan vif
		usleep(e->aizen->time_to_sleep);
		espada_status(e, "\033[1;32mis thinking\033[0m"); // vert vif
	}
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
		espadas[i].id = i + 1;
		espadas[i].aizen = aizen;
		espadas[i].l_zanpakuto = &aizen->zanpakuto[i];
		espadas[i].r_zanpakuto = &aizen->zanpakuto[(i + 1) % aizen->arrancar];
		espadas[i].last_meal_ms = now_ms();
		espadas[i].alive = true;
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
