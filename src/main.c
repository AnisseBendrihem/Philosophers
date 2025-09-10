/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:51 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 22:01:56 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_hueco_mundo	aizen;
	long			born_ms;

	if (!mother_parsing(&aizen, ac, av))
		return (1);
	if (aizen.arrancar == 1)
	{
		born_ms = now_ms();
		printf("%ld 1 has taken a fork\n", now_ms() - (born_ms));
		ft_usleep(aizen.time_to_die);
		printf("\033[1;31m%ld 1 is dead\033[0m\n", now_ms() - (born_ms));
		return (0);
	}
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
