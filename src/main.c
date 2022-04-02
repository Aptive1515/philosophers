/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/04/02 17:52:10 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//int pthread_create (pthread_t *thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);

void *ft_test2(char	*nb)
{
	printf("fct thread 2 \n");
	printf("fct thread : %s\n", nb);

	return(nb);
}

int	main(int argc, char **argv)
{
	t_data	*(*data);
	static pthread_mutex_t	*(*fork);
	int		i;



	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]

	(void)fork;
	(void)argc;
	(void)argv;

	fork = malloc(sizeof(fork) * ft_atoi(argv[1]));
	if(!fork)
		return (0);
	printf("HERE\n");
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		fork[i] = malloc(sizeof(fork));
		printf("fork %d %p\n", i + 1, fork[i]);
		i++;
	}
	data = NULL;
	data = ft_philo_init(data, ft_atoi(argv[1]), fork);
	i = -1;
	while (data[++i])
	{
		printf("philo : %d, fork right %p, fork left %p\n", data[i]->philo->nb, data[i]->fork_r, data[i]->fork_l);
	}



	i = -1;
	while (data[++i])
	{
		pthread_create (&data[i]->philo->thread_philo_nb, NULL, ft_test, data[i]);
		//pthread_join (tab_philo[i]->thread_philo_nb, NULL);
	}

	while(ft_philo_dead(data))
	{}
	return (1);
}
