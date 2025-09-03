/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:03:31 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/03 04:58:02 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>  // pthread_* (threads et mutex)
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // usleep, write
// struct

typedef struct s_agora
{
	int philosophers;  // nombre total de philosophes
	int time_to_die;   // temps max avant de mourir s'ils ne mangent pas
	int time_to_eat;   // temps qu'ils passent à manger
	int time_to_sleep; // temps de repos
	int meals;         // optionnel : nombre de repas à atteindre
}		t_agora;

// utils
void	ft_error(int fd, char *name_error);
char	**ft_split(const char *s, char c);
long	ft_atol(char *str);
int		ft_isdigit(int n);
void	ft_free(char **tab);

//  parcing
int		mother_parsing(t_agora *god, int ac, char **av);

#endif