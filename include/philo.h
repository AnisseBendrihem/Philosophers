/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:03:31 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 20:09:07 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// struct

typedef struct s_hueco_mundo
{
	int				arrancar;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal;
	pthread_mutex_t	state;
	bool			alive;

	pthread_mutex_t	*zanpakuto;
	pthread_mutex_t	order;
	pthread_t shinigami; // monito
	long			born_ms;
}					t_hueco_mundo;

typedef struct s_espada
{
	int				id;
	long			eaten;
	long			last_meal_ms;

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
void				ft_usleep(long ms);

//  parcing
int					mother_parsing(t_hueco_mundo *aizen, int ac, char **av);

// philo
void				espada_status(t_espada *e, char *str);
void				*routine(void *arg);

// forge
int					forge_zanpakuto(t_hueco_mundo *aizen);
void				dismantle_zanpakuto(t_hueco_mundo *aizen);
int					espada_born(t_hueco_mundo *aizen);
int					take_zanpakuto(t_espada *e);
void				drop_zanpakuto(t_espada *e);

#endif
