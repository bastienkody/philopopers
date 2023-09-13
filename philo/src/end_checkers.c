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

/*	si philo n'est pas en train de manger
	et que current_time - last_meal >= tt_die --> Death */
void	check_death(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
	{
		pthread_mutex_lock((*philo)->data->mealtex);
		if (c_time(philo[i]->data->t0) - (philo[i]->last_meal / 1000) >= (unsigned long)philo[i]->data->tt_die)
		{
			pthread_mutex_unlock((*philo)->data->mealtex);
			pthread_mutex_lock((*philo)->data->gutex);
			philo[i]->data->go_on = FALSE;
			pthread_mutex_unlock((*philo)->data->gutex);
			//printf("philo %i, lastmeal:%lu, ctime:%lu \n", i+1, philo[i]->last_meal/1000 ,c_time(philo[i]->data->t0));
			ft_printer(c_time(philo[i]->data->t0), philo[i]->nb, D, philo[i]->data->wutex);
			return ;
		}
		pthread_mutex_unlock((*philo)->data->mealtex);
	}
}

void	check_meal(t_philo **philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock((*philo)->data->mealtex);
	while (philo[++i])
	{
		if (philo[i]->meal_nb != 0)
			return ((void)pthread_mutex_unlock((*philo)->data->mealtex));
	}
	pthread_mutex_unlock((*philo)->data->mealtex);
	pthread_mutex_lock((*philo)->data->gutex);
	philo[0]->data->go_on = FALSE; 
	pthread_mutex_unlock((*philo)->data->gutex);
}
