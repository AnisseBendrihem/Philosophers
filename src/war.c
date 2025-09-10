/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:08:15 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 22:48:29 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_espada *(e) = (t_espada *)arg;
	while (is_alive(e->aizen))
	{
		take_zanpakuto(e);
		pthread_mutex_lock(&e->aizen->state);
		e->last_meal_ms = now_ms();
		pthread_mutex_unlock(&e->aizen->state);
		espada_status(e, "\033[1;35mis eating\033[0m");
		pthread_mutex_lock(&e->aizen->state);
		if (e->aizen->meal > 0 && e->eaten < e->aizen->meal)
		{
			e->eaten++;
			if (e->eaten == e->aizen->meal)
				return (pthread_mutex_unlock(&e->aizen->state),
					drop_zanpakuto(e), NULL);
		}
		pthread_mutex_unlock(&e->aizen->state);
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
	long		t;

	e = (t_espada *)args;
	while (1)
	{
		i = 0;
		while (i < e->aizen->arrancar)
		{
			pthread_mutex_lock(&e->aizen->state);
			t = (now_ms() - e[i].last_meal_ms);
			if (t > e->aizen->time_to_die || all_full(e))
			{
				e->aizen->alive = false;
				pthread_mutex_unlock(&e->aizen->state);
				if (e->eaten == 0)
					espada_death_status(&e[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&e->aizen->state);
			i++;
		}
	}
	return (NULL);
}

static int	create_espadas(t_hueco_mundo *aizen, t_espada *espadas)
{
	int	i;

	i = 0;
	while (i < aizen->arrancar)
	{
		espadas[i].id = i + 1;
		espadas[i].aizen = aizen;
		espadas[i].l_zanpakuto = &aizen->zanpakuto[i];
		espadas[i].r_zanpakuto = &aizen->zanpakuto[(i + 1) % aizen->arrancar];
		espadas[i].last_meal_ms = now_ms();
		espadas[i].eaten = 0;
		if (pthread_create(&espadas[i].thread, NULL, routine, &espadas[i]))
		{
			while (i-- > 0)
				pthread_join(espadas[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	espada_born(t_hueco_mundo *aizen)
{
	int			i;
	t_espada	espadas[200];

	pthread_mutex_init(&aizen->order, NULL);
	pthread_mutex_init(&aizen->state, NULL);
	aizen->alive = true;
	aizen->born_ms = now_ms();
	if (create_espadas(aizen, espadas))
		return (1);
	soul_socity(espadas);
	i = 0;
	while (i < aizen->arrancar)
	{
		if (pthread_join(espadas[i].thread, NULL))
			return (2);
		i++;
	}
	pthread_mutex_destroy(&aizen->state);
	pthread_mutex_destroy(&aizen->order);
	return (0);
}
