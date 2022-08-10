/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:12:11 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 14:21:35 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_philosophers
{
	int				nb;
	pthread_t		thread_philo_nb;
	int				is_eating;
	int				is_spleeping;
	int				is_thinking;
	int				is_dead;
	int				num_fork;

	struct timeval	s_time_last_meal;
	struct timeval	s_time_last;
	struct timeval	s_time_actual;

	unsigned long long	last_meal;
	unsigned long long	time_begin;

	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;

	int				number_philosopher_must_eat;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*to_print;
	pthread_mutex_t	*mutex_dead;
	int				dead_philo;
}	t_data;

/*
PHILO_INIT.C---------------------------------------------------------------------
*/
t_data	**ft_philo_init(t_data *(*data), char **argv);
void	ft_param_to_philo(t_philo *philo, int i);
void	ft_argv_to_philo(t_philo *philo, char **argv);
void	ft_fork_to_philo(t_data *(*data), int nb_philo);
void	ft_init_mutex(t_data *(*data));
/*
FOURCHETTE.C---------------------------------------------------------------------
*/

/*
THREAD.C-------------------------------------------------------------------------
*/
void	*ft_test(void	*arg);
void	ft_take_fork(t_philo *philo, t_data *data);
void	ft_eating(t_philo *philo, t_data *data);
void	ft_sleeping(t_philo *philo, t_data *data);
void	ft_thinking(t_philo *philo, t_data *data);
/*
TIME.C---------------------------------------------------------------------------
*/
unsigned long long	gettime(void);
/*
PHILO_UTILS.C--------------------------------------------------------------------
*/
void	ft_free_all(t_data *(*data));
int		ft_philo_dead(t_data *(*data));
void	ft_died(t_philo *philo, t_data *data);
void	ft_msg( int time ,int philo_nb, char* str);

void ft_etat_philo(t_philo *philo);
#endif
