/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/04/03 09:12:53 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_test(void	*arg)
{
	t_data	*data;

	data = arg;
	ft_thinking(data->philo);
	gettimeofday(&data->philo->s_time_last_meal, NULL);
	while (!data->philo->is_dead)
	{
		if(data->philo->is_eating)
		{
			if(!pthread_mutex_lock (data->fork_r) && !pthread_mutex_lock (data->fork_l))
			{
				//printf("Philo %d, take fork_r %p\n", data->philo->nb, data->fork_r);
				//ft_printf("Philo %d, take fork_l %p\n", data->philo->nb, data->fork_l);
				ft_eating(data->philo);
			}
			else
			{
				//printf("Philo %d, can't take fork_r %p\n", data->philo->nb, data->fork_r);
				//printf("Philo %d, can't take fork_l %p\n", data->philo->nb, data->fork_r);
				pthread_mutex_unlock (data->fork_r);
				pthread_mutex_unlock (data->fork_l);

			}
			if(!pthread_mutex_unlock (data->fork_r) && !pthread_mutex_unlock (data->fork_l))
			{
				//ft_printf("Philo %d, put fork_r %p\n", data->philo->nb, data->fork_r);
				//ft_printf("Philo %d, put fork_l %p\n", data->philo->nb, data->fork_l);
			}
		}
		if (data->philo->is_spleeping == 1)
			ft_sleeping(data->philo);

		gettimeofday(&data->philo->s_time_actual, NULL);
		if (data->philo->s_time_actual.tv_usec - data->philo->s_time_last_meal.tv_usec * 100 >= data->philo->time_to_die *10)
			ft_died(data->philo);
	}
	return(arg);
}

void	ft_eating(t_philo *philo)
{

	/*pthread_mutex_lock (pthread_mutex_t * mutex);
	pthread_mutex_unlock (pthread_mutex_t * mutex);
*/

	philo->is_thinking = 0;
	philo->is_eating = 1;
	printf("%lli %d is eating\n", (gettime() - philo->time_begin)* 100, philo->nb);
	usleep(philo->time_to_eat * 10);
	gettimeofday(&philo->s_time_last_meal, NULL);
	philo->is_eating = 0;
	philo->is_spleeping = 1;

}

void	ft_sleeping(t_philo *philo)
{
	gettimeofday(&philo->s_time_actual, NULL);
	printf("%lli %d is sleeping\n", (gettime() - philo->time_begin)* 100, philo->nb);
	usleep(philo->time_to_sleep * 10);
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	ft_thinking(philo);
}

void	ft_thinking(t_philo *philo)
{
	gettimeofday(&philo->s_time_actual, NULL);
	printf("%lli %d is thinking\n", (gettime() - philo->time_begin)* 100, philo->nb);
	philo->is_eating = 1;
}

void	ft_died(t_philo *philo)
{
	philo->is_dead = 1;
	gettimeofday(&philo->s_time_actual, NULL);
	printf("%lli %d died\n", (gettime() - philo->time_begin) * 100, philo->nb);
}
