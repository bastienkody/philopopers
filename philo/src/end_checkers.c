/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:41:18 by bguillau          #+#    #+#             */
/*   Updated: 2023/09/13 14:41:20 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	CHECKERS :	ret 1 = go_on - ret 0 = end	*/
int	check_death(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
	{
		pthread_mutex_lock((*philo)->data->mealtex);
		if (c_time(philo[i]->data->t0) - (philo[i]->last_meal / 1000) > (unsigned long)philo[i]->data->tt_die)
		{
			pthread_mutex_unlock((*philo)->data->mealtex);
			pthread_mutex_lock((*philo)->data->gutex);
			philo[i]->data->go_on = FALSE;
			pthread_mutex_unlock((*philo)->data->gutex);
			ft_printer(c_time(philo[i]->data->t0), philo[i]->nb, D, philo[i]->data->wutex);
			return (0);
		}
		pthread_mutex_unlock((*philo)->data->mealtex);
	}
	return (1);
}

int	check_meal(t_philo **philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock((*philo)->data->mealtex);
	while (philo[++i])
	{
		//printf("philo%i meal:%i\n", i + 1, (*philo)->meal_nb);
		if (philo[i]->meal_nb != 0)
			return (pthread_mutex_unlock((*philo)->data->mealtex), 1);
	}
	pthread_mutex_unlock((*philo)->data->mealtex);
	pthread_mutex_lock((*philo)->data->gutex);
	philo[0]->data->go_on = FALSE; 
	pthread_mutex_unlock((*philo)->data->gutex);
	return (0);
}

int	check_go_on(t_philo *philo)
{
	pthread_mutex_lock(philo->data->gutex);
	if (!philo->data->go_on)
		return (pthread_mutex_unlock(philo->data->gutex), 0);
	return (pthread_mutex_unlock(philo->data->gutex), 1);
}
