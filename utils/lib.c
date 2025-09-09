/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 02:35:29 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/09 18:28:41 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(int fd, char *name_error)
{
	write(fd, "Error : ", 8);
	printf("%s", name_error);
}

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	else
		return (0);
}

long	ft_atol(char *str)
{
	size_t	i;
	long	signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if ((result * signe) > 2147483647 || (result * signe < -2147483648))
			return (2147483649);
		i++;
	}
	return (result * signe);
}

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	ft_usleep(long ms)
{
	long	start;
	start = now_ms();
	while ((now_ms() - start) < ms)
		usleep(500); // micro-pause pour ne pas bloquer le CPU
}
