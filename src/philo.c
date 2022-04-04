/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/04/04 18:58:20 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**ft_philo_init(t_data *(*data), char **argv)
{
	int					i;
	//unsigned long long	time_begin_all;
	int					nb_philo;

	(void)fork;

	nb_philo = ft_atoi(argv[1]);
	data = malloc(sizeof(data) * (nb_philo + 1));
	//time_begin_all = gettime();
	
	
	i = 0;
	while (i < nb_philo)
	{
	
		data[i] = malloc(sizeof(t_data));
		data[i]->philo = malloc(sizeof(t_philo));
		//data[i]->philo->thread_philo_nb = i;
		data[i]->philo->nb = 1 + i;
		data[i]->philo->num_fork = 1;
		if(i % 2 == 0)
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
		


		
		
		//data[i]->fork_r = &(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER + 1;
		data[i]->fork_r = (pthread_mutex_t*)malloc(sizeof(*(data[i]->fork_r)));
		pthread_mutex_init(data[i]->fork_r, NULL);
		printf("fork[%i] %p\n", i, data[i]->fork_r);


		data[i]->philo->time_to_die = ft_atoi(argv[2]);
		data[i]->philo->time_to_eat = ft_atoi(argv[3]);
		data[i]->philo->time_to_sleep = ft_atoi(argv[4]);

		if (argv[5])
			data[i]->philo->number_of_times_each_philosopher_must_eat =  ft_atoi(argv[5]);
		else
			data[i]->philo->number_of_times_each_philosopher_must_eat = 0;
		
		//data[i]->philo->time_begin = time_begin_all;

		/*if (i + 1 == nb_philo)
			data[i]->fork_l = fork[0];
		else
			data[i]->fork_l = fork[i + 1];
		*/
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

int ft_philo_dead(t_data *(*data))
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i]->philo->is_dead == 1)
			return (0);
		i++;
	}
	return (1);
}
