/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:06:29 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/09 18:30:27 by abendrih         ###   ########.fr       */
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
		if (!valid_number(av[i]) || (ft_atol(av[i]) > INT_MAX))
			return (0);
		i++;
	}
	return (1);
}

static int	init_hueco(t_hueco_mundo *aizen, int ac, char **av)
{
	aizen->arrancar = ft_atol(av[1]);
	if (aizen->arrancar <= 0 || aizen->arrancar > 200)
		return (0);
	aizen->time_to_die = ft_atol(av[2]);
	if (aizen->time_to_die <= 0)
		return (0);
	aizen->time_to_eat = ft_atol(av[3]);
	if (aizen->time_to_eat <= 0)
		return (0);
	aizen->time_to_sleep = ft_atol(av[4]);
	if (aizen->time_to_sleep <= 0)
		return (0);
	if (ac == 6)
	{
		aizen->soul = ft_atol(av[5]);
		if (aizen->soul <= 0)
			return (0);
	}
	return (1);
}

static void	empty_mundo(t_hueco_mundo *aizen)
{
	aizen->arrancar = 0;
	aizen->time_to_die = 0;
	aizen->time_to_eat = 0;
	aizen->time_to_sleep = 0;
	aizen->born_ms = 0;
	aizen->soul = 0;
}

int	mother_parsing(t_hueco_mundo *aizen, int ac, char **av)
{
	empty_mundo(aizen);
	if (ac < 5 || ac > 6)
		return (ft_error(2, "invalid number of arguments\n"), 0);
	if (!valid_all_num(ac, av))
		return (ft_error(2, "invalid arguments\n"), 0);
	if (!init_hueco(aizen, ac, av))
		return (ft_error(2,
				"value need to be above 0 and arrancar under 200\n"), 0);
	return (1);
}
