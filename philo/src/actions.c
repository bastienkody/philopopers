/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/17 15:10:06 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	futex_lock(t_philo *philo)
{
	pthread_mutex_lock(philo->data->futex[philo->nb - 1]);
	ft_printer(c_time(philo->data->t0), philo->nb, F, philo->data->wutex);
	if (philo->data->nb_philo > 1)
	{
		if (philo->nb < philo->data->nb_philo)
			pthread_mutex_lock(philo->data->futex[philo->nb]);
		else
			pthread_mutex_lock(philo->data->futex[0]);
		ft_printer(c_time(philo->data->t0), philo->nb, F, philo->data->wutex);
		return (1);
	}
	return (0);
}

void	futex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->data->futex[philo->nb - 1]);
	if (philo->data->nb_philo > 1)
	{
		if (philo->nb < philo->data->nb_philo)
			pthread_mutex_unlock(philo->data->futex[philo->nb]);
		else
			pthread_mutex_unlock(philo->data->futex[0]);
	}
}

void	eatp(t_philo *philo)
{
	pthread_mutex_lock(philo->data->gutex);
	if (!philo->data->go_on)
		return ((void) pthread_mutex_unlock(philo->data->gutex));
	pthread_mutex_unlock(philo->data->gutex);
	if (futex_lock(philo)) // more than one philo
	{
		ft_printer(c_time(philo->data->t0), philo->nb, E, philo->data->wutex);
		pthread_mutex_lock(philo->data->mealtex);
		philo->last_meal = c_time(philo->data->t0) * 1000;
		philo->meal_nb -= 1;
		pthread_mutex_unlock(philo->data->mealtex);
	}
	ft_usleep(philo->data->tt_eat * 1000);
	futex_unlock(philo);
	return ((void) sleepp(philo));
}

void	sleepp(t_philo *philo)
{
	pthread_mutex_lock(philo->data->gutex);
	if (!philo->data->go_on)
		return ((void) pthread_mutex_unlock(philo->data->gutex));
	pthread_mutex_unlock(philo->data->gutex);
	ft_printer(c_time(philo->data->t0), philo->nb, S, philo->data->wutex);
	ft_usleep(philo->data->tt_sleep * 1000);
	return ((void) thinkp(philo));
}

void	thinkp(t_philo *philo)
{
	pthread_mutex_lock(philo->data->gutex);
	if (!philo->data->go_on)
		return ((void) pthread_mutex_unlock(philo->data->gutex));
	pthread_mutex_unlock(philo->data->gutex);
	ft_printer(c_time(philo->data->t0), philo->nb, T, philo->data->wutex);
	//ft_usleep(500);
	return ((void) eatp(philo));
}
