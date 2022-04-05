/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/04/05 20:06:46 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**ft_philo_init(t_data *(*data), char **argv)
{
	int		i;
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	data = malloc(sizeof(data) * (nb_philo + 1));
	i = 0;
	while (i < nb_philo)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->philo = malloc(sizeof(t_philo));
		data[i]->philo->nb = 1 + i;
		data[i]->philo->num_fork = 1;
		if (i % 2 == 0)
		{
			data[i]->philo->is_eating = 1;
			data[i]->philo->is_thinking = 0;
		}	
		else
		{
			data[i]->philo->is_eating = 0;
			data[i]->philo->is_thinking = 1;
		}		
		data[i]->philo->is_dead = 0;
		data[i]->fork_r = (pthread_mutex_t*)malloc(sizeof(*(data[i]->fork_r)));
		pthread_mutex_init(data[i]->fork_r, NULL);
		printf("fork[%i] %p\n", i, data[i]->fork_r);
		data[i]->philo->time_to_die = ft_atoi(argv[2]);
		data[i]->philo->time_to_eat = ft_atoi(argv[3]);
		data[i]->philo->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			data[i]->philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			data[i]->philo->number_of_times_each_philosopher_must_eat = 0;
		i++;
	}
	data[i] = NULL;
	i = 0;
	while (i < nb_philo)
	{
		if (i + 1 == nb_philo)
			data[i]->fork_l = data[0]->fork_r;
		else
			data[i]->fork_l = data[i + 1]->fork_r;
		i++;
	}
	return (data);
}

int	ft_philo_dead(t_data *(*data))
{
	int	i;

	i = 0;
	while (data[i])
	{
		if(!pthread_mutex_lock(data[i]->mutex_dead))
		{
			if (!data[i]->dead_philo)
			{
				pthread_mutex_unlock(data[i]->mutex_dead);
				return (0);
			}
			pthread_mutex_unlock(data[i]->mutex_dead);
		}	
		i++;
	}
	return (1);
}

void	ft_init_mutex(t_data *(*data))
{
	pthread_mutex_t	*to_print;
	pthread_mutex_t	*mutex_dead;
	char			*c;
	
	int				i;

	i = 0;

	to_print = (pthread_mutex_t*)malloc(sizeof(*(to_print)));
	mutex_dead = (pthread_mutex_t*)malloc(sizeof(*(mutex_dead)));
	c = malloc(sizeof(char) + 2);
	c[0] = 'c';
	c[1] = '\0';

	pthread_mutex_init(to_print, NULL);
	pthread_mutex_init(mutex_dead, NULL);
	//pthread_mutex_init(dead_philo, NULL);

//	printf("mutex to_print		%p\n", to_print);
//	printf("mutex dead_philo 	%p\n", dead_philo);

	while (data[i])
	{
		data[i]->to_print = to_print;
		data[i]->mutex_dead = mutex_dead;
		data[i]->dead_philo = c;
	//	printf("data mutex to_print	%p\n", data[i]->to_print);
	//	printf("data mutex dead_philo	%p\n", data[i]->dead_philo);
	//	printf("****philo %i dead_philo %s, int = %p\n", data[i]->philo->nb, data[i]->dead_philo, data[i]->dead_philo);
		i++;
	}


}