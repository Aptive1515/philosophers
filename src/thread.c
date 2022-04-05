/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/04/05 20:09:41 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void ft_etat_philo(t_philo *philo)
{
	printf("************************************\n");
	printf("Philo %i, eating %i, sleeping %i, think %i, dead %i, last meal %lli\n\n",
	 philo->nb, philo->is_eating, philo->is_spleeping, philo->is_thinking, philo->is_dead, philo->last_meal);
}

void	*ft_test(void *arg)
{
	t_data	*data;
	int		j;

	j = 0;
	data = arg;
	data->philo->time_begin = gettime();
	data->philo->last_meal = gettime();



//	printf("philo %i dead_philo %p int = %c\n", data->philo->nb,data->dead_philo, *data->dead_philo);
	//pthread_mutex_lock(data->dead_philo);

	while (!data->philo->is_dead)
	{


	//	printf("**************test : %i\n", i);
		if (data->philo->is_eating)
		{			
			if (!pthread_mutex_lock(data->fork_r))
				j++;
				//printf("philo %i has taken the fork_r %p\n", data->philo->nb, data->fork_r);
			if (!pthread_mutex_lock(data->fork_l))
			{
				//printf("philo %i has taken the fork_l %p\n", data->philo->nb, data->fork_l);
				ft_eating(data->philo, data);
			}
			if (!pthread_mutex_unlock(data->fork_r))
				j++;	//printf("philo %i has DROP the fork_r %p\n", data->philo->nb, data->fork_r);
			if (!pthread_mutex_unlock(data->fork_l))
				j++;//printf("philo %i has DROP the fork_l %p\n", data->philo->nb, data->fork_l);
		}
		if (data->philo->is_spleeping)
			ft_sleeping(data->philo, data);
		if (data->philo->is_thinking)
		{
			ft_thinking(data->philo, data);
		}
		if ((gettime() - data->philo->last_meal) * 100 >= (unsigned long long)data->philo->time_to_die)
			ft_died(data->philo, data);
	}
	return (arg);
}

void	ft_eating(t_philo *philo, t_data *data)
{
	(void)data;
	//printf("here\n");
	//printf("deadphilo %i\n", *data->dead_philo);
	while(pthread_mutex_lock(data->to_print))
	{}
	while(pthread_mutex_lock(data->mutex_dead))
	{}
	if(data->dead_philo)
		ft_printf("%l %d is eating\n", (gettime() - philo->time_begin) * 100, philo->nb);
	pthread_mutex_unlock(data->to_print);
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 0;
	philo->is_spleeping = 1;
	philo->last_meal = gettime();
	usleep(philo->time_to_eat * 10);
}

void	ft_sleeping(t_philo *philo, t_data *data)
{
	//printf("here2\n");
	(void)data;
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	while(pthread_mutex_lock(data->to_print))
	{}
	while(pthread_mutex_lock(data->mutex_dead))
	{}
	if(data->dead_philo)
		ft_printf("%l %d is sleeping\n", (gettime() - philo->time_begin) * 100, philo->nb);
	pthread_mutex_unlock(data->to_print);
	pthread_mutex_unlock(data->mutex_dead);
	usleep(philo->time_to_sleep * 10);
	ft_thinking(philo, data);
}

void	ft_thinking(t_philo *philo, t_data *data)
{
	(void)data;
	//printf("here3\n");
	gettimeofday(&philo->s_time_actual, NULL);
	while(pthread_mutex_lock(data->to_print))
	{}
	while(pthread_mutex_lock(data->mutex_dead))
	{}
	if(data->dead_philo)
		ft_printf("%l %d is thinking\n", (gettime() - philo->time_begin) * 100, philo->nb);
	pthread_mutex_unlock(data->mutex_dead);
	pthread_mutex_unlock(data->to_print);
	philo->is_eating = 1;
	philo->is_thinking = 0;
}

void	ft_died(t_philo *philo, t_data *data)
{
	(void)data;
	int i;
	
//	printf("\n***************philo %i dead_philo %p\n", data->philo->nb,data->dead_philo);
//	printf("dead_philo %i\n", *data->dead_philo);

	
	i = 1;
//	printf("here4\n");
	while(pthread_mutex_lock(data->mutex_dead))
	{}
	//printf("here5\n");
	
	//printf("dead_philo %i/\n", *data->dead_philo);
	if(data->dead_philo)
		printf("%lli %d died\n", (gettime() - philo->time_begin) * 100, philo->nb);
	data->dead_philo = NULL;
	pthread_mutex_unlock(data->mutex_dead);
}
