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

void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo*) phil;
	printf("salut from philo %i %lu\n", ((t_philo*) philo)->nb, ((t_philo*) philo)->t_id);
	


	return (NULL);
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

	i = -1;
	while (philo[++i])
	{
		if (pthread_join(philo[i]->t_id, NULL))
			printf("pb joining t_id %luWhat can i do??\n", philo[i]->t_id);
		//else
			//printf("joined t_id %lu\n", data->philo[i]->t_id);
	}
	return (printf("launcher returned\n"), (void) 0);
}
