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

/*	hould i set t0 here? how?	*/
void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *) phil;
	philo->last_meal = 0;
	if (!(philo->nb & 1)) //pairs
		eatp(philo);
	else 
	{
		ft_usleep(500);
		thinkp(philo);
	}
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
	while (TRUE)
	{	
		ft_usleep(500);
		check_meal(philo);
		check_death(philo);
		pthread_mutex_lock((*philo)->data->gutex);
		if (!(*philo)->data->go_on)
		{
			pthread_mutex_unlock((*philo)->data->gutex);
			break;
		}
		pthread_mutex_unlock((*philo)->data->gutex);

	}
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
