/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:51 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/12 13:24:07 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_hueco_mundo	aizen;

	if (!mother_parsing(&aizen, ac, av))
		return (1);
	if (forge_zanpakuto(&aizen) != 0)
		return (2);
	if (espada_born(&aizen) != 0)
	{
		dismantle_zanpakuto(&aizen);
		return (3);
	}
	dismantle_zanpakuto(&aizen);
	return (0);
}
