/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:03:31 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/10 22:16:19 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef struct s_hueco_mundo
{
	int				arrancar;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal;

	bool			alive;

	long			born_ms;
	pthread_t		shinigami;

	pthread_mutex_t	state;
	pthread_mutex_t	order;
	pthread_mutex_t	*zanpakuto;
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

/* ************************************************************************** */
/*                                PROTOTYPES                                  */
/* ************************************************************************** */

/* ----------------------------- utils/lib.c -------------------------------- */
void				ft_error(int fd, char *name_error);
long				ft_atol(char *str);
int					ft_isdigit(int n);
long				now_ms(void);
void				ft_usleep(long ms);

/* --------------------------- parsing/parsing.c ---------------------------- */
int					mother_parsing(t_hueco_mundo *aizen, int ac, char **av);

/* ------------------------- src/espadas_life.c ----------------------------- */
void				espada_status(t_espada *e, char *str);
void				espada_death_status(t_espada *e);
int					all_full(t_espada *e);
bool				is_alive(t_hueco_mundo *a);

/* --------------------------- src/forge.c ---------------------------------- */
int					forge_zanpakuto(t_hueco_mundo *aizen);
void				dismantle_zanpakuto(t_hueco_mundo *aizen);
int					take_zanpakuto(t_espada *e);
void				drop_zanpakuto(t_espada *e);

/* --------------------------- src/war.c ------------------------------------ */
void				*routine(void *arg);
void				*soul_socity(void *args);
int					espada_born(t_hueco_mundo *aizen);

#endif /* PHILO_H */
