/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 04:56:58 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/08 05:08:47 by abendrih         ###   ########.fr       */
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
