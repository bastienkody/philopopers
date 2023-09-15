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

	philo = (t_philo *) phil;
	pthread_mutex_lock(philo->data->mealtex);
	philo->last_meal = 0;
	pthread_mutex_unlock(philo->data->mealtex);
	if (!(philo->nb & 1)) //pairs
		eating(philo);
	else 
		thinking(philo);
	return (NULL);
}

/*	check meals only if meal_nb arg given	*/
void	launcher(t_philo **philo, int argc)
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
		ft_usleep((*philo)->data->tt_die);
		if (argc == 6 && !check_meal(philo))
			break ;
		if (!check_death(philo))
			break ;
	}
	i = -1;
	while (philo[++i])
	{
		if (pthread_join(philo[i]->t_id, NULL))
			printf("pb joining t_id %luWhat can i do??\n", philo[i]->t_id);
	}
	//return (printf("launcher returned\n"), (void) 0);
}
