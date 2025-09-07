/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:03:31 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/07 04:27:00 by abendrih         ###   ########.fr       */
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

// philo.h
typedef struct s_hueco_mundo
{
	int				arrancar;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				soul;

	pthread_mutex_t	*zanpakuto;
	pthread_mutex_t	order;
	long			start_ms;
}					t_hueco_mundo;

typedef struct s_espada
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*l_zanpakuto;
	pthread_mutex_t	*r_zanpakuto;
	t_hueco_mundo	*aizen;
}					t_espada;

// utils
void				ft_error(int fd, char *name_error);
long				ft_atol(char *str);
int					ft_isdigit(int n);
long				now_ms(void);

//  parcing
int					mother_parsing(t_hueco_mundo *aizen, int ac, char **av);

#endif
