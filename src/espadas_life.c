/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espadas_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:03:22 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/09 21:53:15 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	espada_status(t_espada *e, char *str)
{
	long	t;

	pthread_mutex_lock(&e->aizen->order);
	if (e->aizen->alive)
	{
		t = now_ms() - (e->aizen->born_ms);
		printf("Espada %d  at %ld %s\n", e->id, t, str);
	}
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
	if (e->id % e->aizen->arrancar == 0)
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
	while (e->aizen->alive == true)
	{
		take_zanpakuto(e);
		espada_status(e, "\033[1;35mis eating\033[0m");
		ft_usleep(e->aizen->time_to_eat);
		drop_zanpakuto(e);
		espada_status(e, "\033[1;36mis sleeping\033[0m");
		ft_usleep(e->aizen->time_to_sleep);
		espada_status(e, "\033[1;32mis thinking\033[0m");
	}
	return (NULL);
}

void	*soul_socity(void *args)
{
	t_espada	*e;
	int			i;

	e = (t_espada *)args;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < e->aizen->arrancar)
		{
			if ((now_ms() - e[i].last_meal_ms) > e->aizen->time_to_die)
			{
				e->aizen->alive = false;
				espada_status(e, "\033[1;31mis dead\033[0m");
				return (NULL);
			}
		}
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
		espadas[i].aizen->alive = true;
		if (pthread_create(&espadas[i].thread, NULL, routine, &espadas[i]))
			return (1);
		i++;
	}
	i = 0;
	soul_socity(espadas);
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
