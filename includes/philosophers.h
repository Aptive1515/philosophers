/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:12:11 by aptive            #+#    #+#             */
/*   Updated: 2022/03/13 16:10:49 by aptive           ###   ########.fr       */
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
} t_philo;




typedef struct s_fork
{
	int				nb;
	pthread_t		thread_nb;

} t_fork;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;

} t_data;
/*
PHILO.C--------------------------------------------------------------------------
*/
t_data	**ft_philo_init(t_data *(*data), int nb_philo, pthread_mutex_t *(*fork));
int		ft_philo_dead(t_data *(*data));
/*
FOURCHETTE.C---------------------------------------------------------------------
*/
t_fork	**ft_init_fork(t_fork *(*tab_fork), int nb_philo);
/*
THREAD.C--------------------------------------------------------------------------
*/
void	*ft_test(void	*arg);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_died(t_philo *philo);
/*
THREAD.C--------------------------------------------------------------------------
*/
unsigned long long	gettime(void);

#endif
