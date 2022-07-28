/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/07/28 15:22:21 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void ft_etat_philo(t_philo *philo)
{
	printf("************************************\n");
	printf("Philo %i, eating %i, sleeping %i, think %i, dead %i, last meal %lli\n\n",
	 philo->nb, philo->is_eating, philo->is_spleeping, philo->is_thinking, philo->is_dead, philo->last_meal);
}

void	ft_putstr_philo(int nb_philo, int timer, char *str)
{
	ft_putnbr_fd(nb_philo, 1);
	ft_putnbr_fd(timer, 1);
	ft_putstr_fd(str, 1);
}

void	*ft_test(void *arg)
{
	t_data	*data;
	int		k;

	k = 0;
	data = arg;
	data->philo->time_begin = gettime();
	data->philo->last_meal = gettime();
	while (!data->dead_philo)
	{
		if (data->philo->is_eating)
		{
			if (!pthread_mutex_lock(data->fork_r))
				k++;
			if (!pthread_mutex_lock(data->fork_l))
				ft_eating(data->philo, data);
			if (!pthread_mutex_unlock(data->fork_r))
				k++;
			if (!pthread_mutex_unlock(data->fork_l))
				k++;
		}
		if (data->philo->is_spleeping)
			ft_sleeping(data->philo, data);
		if (data->philo->is_thinking)
			ft_thinking(data->philo, data);
		if ((gettime() - data->philo->last_meal) * 100 >= (unsigned long long)data->philo->time_to_die)
			ft_died(data->philo, data);
	}
	return (arg);
}

void	ft_eating(t_philo *philo, t_data *data)
{
	(void)data;
	while (pthread_mutex_lock(data->to_print))
	{}
	while (pthread_mutex_lock(data->mutex_dead))
	{}
	if (!data->dead_philo)
		ft_putstr_philo(philo->nb, (gettime() - philo->time_begin), " is eating\n");
	pthread_mutex_unlock(data->to_print);
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 0;
	philo->is_spleeping = 1;
	philo->last_meal = gettime();
	usleep(philo->time_to_eat * 100);
}

void	ft_sleeping(t_philo *philo, t_data *data)
{
	(void)data;
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	while (pthread_mutex_lock(data->to_print))
	{}
	while (pthread_mutex_lock(data->mutex_dead))
	{}
	if (!data->dead_philo)
		ft_putstr_philo(philo->nb, (gettime() - philo->time_begin), " is sleeping\n");
	pthread_mutex_unlock(data->to_print);
	pthread_mutex_unlock(data->mutex_dead);
	usleep(philo->time_to_sleep * 100);
	ft_thinking(philo, data);
}

void	ft_thinking(t_philo *philo, t_data *data)
{
	(void)data;
	gettimeofday(&philo->s_time_actual, NULL);
	while (pthread_mutex_lock(data->to_print))
	{}
	while (pthread_mutex_lock(data->mutex_dead))
	{}
	if (!data->dead_philo)
		ft_putstr_philo(philo->nb, (gettime() - philo->time_begin), " is thinking\n");
	pthread_mutex_unlock(data->mutex_dead);
	pthread_mutex_unlock(data->to_print);
	philo->is_eating = 1;
	philo->is_thinking = 0;
}

void	ft_died(t_philo *philo, t_data *data)
{
	(void)data;
	while(pthread_mutex_lock(data->mutex_dead))
	{}
	if(!data->dead_philo)
		ft_putstr_philo(philo->nb, (gettime() - philo->time_begin), " died\n");
	data->dead_philo = 1;
	pthread_mutex_unlock(data->mutex_dead);
}
