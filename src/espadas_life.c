/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espadas_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:03:22 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 20:41:03 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_alive(t_hueco_mundo *a)
{
	bool	v;

	pthread_mutex_lock(&a->state);
	v = a->alive;
	pthread_mutex_unlock(&a->state);
	return (v);
}

void	espada_status(t_espada *e, char *str)
{
	long	t;

	if (is_alive(e->aizen))
	{
		t = now_ms() - (e->aizen->born_ms);
		pthread_mutex_lock(&e->aizen->order);
		printf("Espada %d  at %ld %s\n", e->id, t, str);
		pthread_mutex_unlock(&e->aizen->order);
	}
}

void	espada_death_status(t_espada *e)
{
	pthread_mutex_lock(&e->aizen->order);
	printf("\033[1;31mEspada %d  at %ld is dead\033[0m\n", e->id, now_ms()
		- (e->aizen->born_ms));
	pthread_mutex_unlock(&e->aizen->order);
}

void	*routine(void *arg)
{
	t_espada	*e;

	e = (t_espada *)arg;
	while (is_alive(e->aizen))
	{
		take_zanpakuto(e);
		pthread_mutex_lock(&e->aizen->state);
		e->last_meal_ms = now_ms();
		pthread_mutex_unlock(&e->aizen->state);
		espada_status(e, "\033[1;35mis eating\033[0m");
		pthread_mutex_lock(&e->aizen->state);
		if (e->aizen->meal > 0)
			e->eaten++;
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
			if (t > e->aizen->time_to_die || (e->eaten > 0
					&& e->aizen->meal == e->eaten))
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

int	espada_born(t_hueco_mundo *aizen)
{
	int			i;
	t_espada	*espadas;

	pthread_mutex_init(&aizen->order, NULL);
	pthread_mutex_init(&aizen->state, NULL);
	aizen->alive = true;
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
		espadas[i].eaten = 0;
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
	pthread_mutex_destroy(&aizen->state);
	pthread_mutex_destroy(&aizen->order);
	free(espadas);
	return (0);
}
