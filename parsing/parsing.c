/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:06:29 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/03 04:56:45 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	valid_number(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	valid_all_num(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!valid_number(av[i]) || ft_atol(av[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

static void	init_agora(t_agora *god, int ac, char **av)
{
	god->philosophers = ft_atol(av[1]);
	god->time_to_die = ft_atol(av[2]);
	god->time_to_eat = ft_atol(av[3]);
	god->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		god->meals = ft_atol(av[5]);
}

int	mother_parsing(t_agora *god, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_error(2, "invalid number of arguments"), 0);
	if (!valid_all_num(ac, av))
		return (ft_error(2, "invalid arguments"), 0);
	init_agora(god, ac, av);
	return (1);
}
