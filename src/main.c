/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/04/04 18:58:42 by tdelauna         ###   ########.fr       */
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
/*	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	
	int retour = pthread_mutex_lock (&mutex);
	printf("retour : %i\n", retour);
	retour = pthread_mutex_unlock (&mutex);
	printf("retour : %i\n", retour);

	(void)argc;
	(void)argv;*/


	t_data	*(*data);
	//static pthread_mutex_t	*(*fork);
	int		i;
	int number_of_philosophers;

	(void)fork;
	(void)argc;
	(void)argv;






	number_of_philosophers = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
		return (1);
	//fork = malloc(sizeof(fork) * number_of_philosophers);
	//if(!fork)
	//	return (0);
	i = 0;
	/*while (i < ft_atoi(argv[1]))
	{
		//fork[i] = (pthread_mutex_t)malloc(sizeof(pthread_mutex_t));
		//pthread_mutex_init(&fork, NULL);
		fork[i] = &(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		printf("fork%i %p\n", i, fork[i]);
		i++;
	}*/

	
	data = NULL;
	data = ft_philo_init(data, argv);
	i = -1;
	while (data[++i])
	{
		//ft_etat_philo(data[i]->philo);



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
