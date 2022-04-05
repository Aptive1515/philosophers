/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/04/05 20:06:27 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
//	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	t_data	*(*data);
	int		i;
	int		number_of_philosophers;

	(void)argc;
	(void)argv;
	number_of_philosophers = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	data = NULL;
	data = ft_philo_init(data, argv);
	ft_init_mutex(data);

	i = -1;
/*	while (data[++i])
	{
		printf("****philo %i dead_philo %p, int = %s\n", data[i]->philo->nb,data[i]->dead_philo, data[i]->dead_philo);
	}*/
	i = -1;
	while (data[++i])
	{
		pthread_create(&data[i]->philo->thread_philo_nb, NULL, ft_test, data[i]);
		//pthread_join (tab_philo[i]->thread_philo_nb, NULL);
	}
	while (ft_philo_dead(data))
	{}
	return (1);
}
