/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 04:56:58 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 17:28:56 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	forge_zanpakuto(t_hueco_mundo *aizen)
{
	int	i;

	i = 0;
	aizen->zanpakuto = malloc(sizeof(pthread_mutex_t) * aizen->arrancar);
	if (!aizen->zanpakuto)
		return (1);
	while (i < aizen->arrancar)
	{
		if (pthread_mutex_init(&aizen->zanpakuto[i], NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}

void	dismantle_zanpakuto(t_hueco_mundo *aizen)
{
	int	i;

	i = 0;
	if (!aizen->zanpakuto)
		return ;
	while (i < aizen->arrancar)
	{
		pthread_mutex_destroy(&aizen->zanpakuto[i]);
		i++;
	}
	free(aizen->zanpakuto);
	aizen->zanpakuto = NULL;
}

int	take_zanpakuto(t_espada *e)
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

void	drop_zanpakuto(t_espada *e)
{
	if (e->l_zanpakuto == e->r_zanpakuto)
	{
		pthread_mutex_unlock(e->l_zanpakuto);
		return ;
	}
	pthread_mutex_unlock(e->l_zanpakuto);
	pthread_mutex_unlock(e->r_zanpakuto);
}
