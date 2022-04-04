/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/04/04 19:15:41 by tdelauna         ###   ########.fr       */
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

	//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



//	pthread_mutex_init(data->fork_r, NULL);
	data = arg;
	data->philo->time_begin = gettime();
	data->philo->last_meal = gettime();

	//printf("time_begin = %lli\n", data->philo->time_begin);
	//printf("last meal  = %lli\n", data->philo->last_meal);


	//printf("time test %lli\n",  data->philo->time_begin - gettime());
	
	//ft_etat_philo(data->philo);

/*	
	usleep(7000);
	printf("time to die : %lli\n", (unsigned long long) data->philo->time_to_die * 10);
	printf("%lli ms\n", (gettime() - data->philo->last_meal) * 100);


	if ((gettime() - data->philo->last_meal) * 100 >= (unsigned long long)data->philo->time_to_die)
		printf("dieeeeee");*/
	//ft_etat_philo(data->philo);
/*	if (data->philo->is_eating)
	{
		if (!pthread_mutex_lock(data->fork_r))
					printf("philo %i has TAKEN the fork_r %p\n", data->philo->nb, data->fork_r);
		if (!pthread_mutex_lock(data->fork_l))
			printf("philo %i has TAKEN the fork_l %p\n", data->philo->nb, data->fork_l);


		if (!pthread_mutex_unlock(data->fork_r))
					printf("philo %i has DROP the fork_r %p\n", data->philo->nb, data->fork_r);
		if (!pthread_mutex_unlock(data->fork_l))
			printf("philo %i has DROP the fork_l %p\n", data->philo->nb, data->fork_l);
		
	}

*/
int j = 0;
	while (!data->philo->is_dead)
	{
		
		if (data->philo->is_eating)
		{
			
			if (!pthread_mutex_lock(data->fork_r))
				j++;
				//printf("philo %i has taken the fork_r %p\n", data->philo->nb, data->fork_r);
			if (!pthread_mutex_lock(data->fork_l))
			{
				//printf("philo %i has taken the fork_l %p\n", data->philo->nb, data->fork_l);
				ft_eating(data->philo);
			}
			if (!pthread_mutex_unlock(data->fork_r))
				j++;	//printf("philo %i has DROP the fork_r %p\n", data->philo->nb, data->fork_r);
			if (!pthread_mutex_unlock(data->fork_l))
				j++;//printf("philo %i has DROP the fork_l %p\n", data->philo->nb, data->fork_l);
		}
		if (data->philo->is_spleeping)
			ft_sleeping(data->philo);
		if (data->philo->is_thinking)
		{
			ft_thinking(data->philo);
		}
		if ((gettime() - data->philo->last_meal) * 100 >= (unsigned long long)data->philo->time_to_die)
			ft_died(data->philo);
	}
	return(arg);
}

void	ft_eating(t_philo *philo)
{
	printf("%lli %d is eating\n", (gettime() - philo->time_begin) * 100, philo->nb);
	philo->is_eating = 0;
	philo->is_spleeping = 1;
	philo->last_meal = gettime();
	usleep(philo->time_to_eat * 10);
	
	philo->is_eating = 0;
	philo->is_spleeping = 1;
}

void	ft_sleeping(t_philo *philo)
{

	printf("%lli %d is sleeping\n", (gettime() - philo->time_begin) * 100, philo->nb);
	usleep(philo->time_to_sleep * 10);
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	ft_thinking(philo);
}

void	ft_thinking(t_philo *philo)
{
	gettimeofday(&philo->s_time_actual, NULL);
	printf("%lli %d is thinking\n", (gettime() - philo->time_begin) * 100, philo->nb);
	philo->is_eating = 1;
	philo->is_thinking = 0;
}

void	ft_died(t_philo *philo)
{
	philo->is_dead = 1;
	printf("%lli %d died\n", (gettime() - philo->time_begin) * 100, philo->nb);
}
