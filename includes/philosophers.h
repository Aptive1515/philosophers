/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:12:11 by aptive            #+#    #+#             */
/*   Updated: 2022/04/05 20:00:23 by tdelauna         ###   ########.fr       */
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
	
	int				number_of_times_each_philosopher_must_eat;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*to_print;
	pthread_mutex_t	*mutex_dead;
	char			*dead_philo;
}	t_data;

/*
PHILO.C--------------------------------------------------------------------------
*/
t_data	**ft_philo_init(t_data *(*data), char **argv);
int		ft_philo_dead(t_data *(*data));
void	ft_init_mutex(t_data *(*data));
/*
FOURCHETTE.C---------------------------------------------------------------------
*/

/*
THREAD.C-------------------------------------------------------------------------
*/
void	*ft_test(void	*arg);
void	ft_eating(t_philo *philo, t_data *data);
void	ft_sleeping(t_philo *philo, t_data *data);
void	ft_thinking(t_philo *philo, t_data *data);
void	ft_died(t_philo *philo, t_data *data);
/*
THREAD.C-------------------------------------------------------------------------
*/
unsigned long long	gettime(void);


void ft_etat_philo(t_philo *philo);
#endif
