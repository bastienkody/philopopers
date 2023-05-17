/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/08 19:58:56 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* simulation starts : set t0, gives activity to philo */
void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *) phil;
	//printf("salut from philo %i\n", ((t_philo *) philo)->nb);
	//if (!philo->data->t0)
		//gettimeofday(philo->data->t0, NULL);
	philo->last_meal = 0;
	if (!(philo->nb & 1)) //pairs
		eatp(philo);
	else 
		thinkp(philo);
	return (printf("routine returned philo %i\n", philo->nb), NULL);
}

void	launcher(t_philo **philo)
{
	pthread_t	thread;
	int			i;

	
	i = -1;
	while (philo[++i])
	{
		if (pthread_create(&thread, NULL, &routine, philo[i]))
			return (phcreate_failure_mgmt(philo, i + 1), (void) 0);
		else
			philo[i]->t_id = thread;
	}

	// main thread must check deaths + nb_meals here
	//ft_usleep(10000000);
	//philo[0]->data->go_on = FALSE;

	i = -1;
	while (philo[++i])
	{
		if (pthread_join(philo[i]->t_id, NULL))
			printf("pb joining t_id %luWhat can i do??\n", philo[i]->t_id);
		else
			printf("joined t_id %lu\n", philo[i]->t_id);
	}
	return (printf("launcher returned\n"), (void) 0);
}
