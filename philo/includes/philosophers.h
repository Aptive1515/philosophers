/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:12:11 by aptive            #+#    #+#             */
/*   Updated: 2022/08/29 15:15:33 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philosophers
{
	int				nb;
	pthread_t		thread_philo_nb;
	int				is_eating;
	int				is_spleeping;
	int				is_thinking;
	int				is_dead;
	int				have_meal;
	int				nb_philo;
	int				last_meal;
	int				time_begin;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;

	int				nb_philo_must_eat;
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
t_data	**philo_init(t_data *(*data), char **argv);
void	param_to_philo(t_philo *philo, int i);
void	argv_to_philo(t_philo *philo, char **argv);
void	fork_to_philo(t_data *(*data), int nb_philo);
void	init_mutex(t_data *(*data));
/*
ACTION.C-------------------------------------------------------------------------
*/
void	take_fork(t_philo *philo, t_data *data);
void	eating(t_philo *philo, t_data *data);
void	sleeping(t_philo *philo, t_data *data);
void	thinking(t_philo *philo, t_data *data);

/*
THREAD.C-------------------------------------------------------------------------
*/
void	*routine(void	*arg);
int		witch_k(t_data *data);
void	eating_odd_even(t_data *data);
/*
TIME.C---------------------------------------------------------------------------
*/
int		gettime(void);
void	msg(int time, int philo_nb, char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_exit_free(t_data *(*data));

/*
PHILO_UTILS.C--------------------------------------------------------------------
*/
void	free_all(t_data *(*data));
void	philo_dead(t_data *(*data), int nb_philo, int time_to_dead);
void	died(t_philo *philo, t_data *data);
/*
UTILS.C--------------------------------------------------------------------------
*/
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
char	*ft_strjoin_gnl(char *s1, char *s2);

/*
UTILS_2.C------------------------------------------------------------------------
*/
int		ft_strlen(const char *str);
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elementCount, size_t elementSize);
int		ft_itoa_size(int n);
char	*ft_itoa(int n);

#endif
