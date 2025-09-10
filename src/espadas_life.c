/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espadas_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:03:22 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 22:18:10 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	all_full(t_espada *e)
{
	int	i;

	i = 0;
	while (i < e->aizen->arrancar)
	{
		if (e[i].eaten == e->aizen->meal)
		{
			i++;
		}
		else
			return (0);
	}
	return (1);
}

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
		printf("%ld %d %s\n", t, e->id, str);
		pthread_mutex_unlock(&e->aizen->order);
	}
}

void	espada_death_status(t_espada *e)
{
	pthread_mutex_lock(&e->aizen->order);
	printf("%ld %d died\n", now_ms() - (e->aizen->born_ms), e->id);
	pthread_mutex_unlock(&e->aizen->order);
}
