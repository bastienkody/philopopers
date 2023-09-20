/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/09/20 16:27:47 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	ret 0 : not go_on, no fork locked
	ret 1 : solo philo, single fork locked
	ret 2 : ok two forks locked		*/
int	futex_lock(t_philo *philo)
{
	if (!check_go_on(philo))
		return (0);
	pthread_mutex_lock(philo->data->futex[philo->nb - 1]);
	if (check_go_on(philo))
		ft_printer(c_time(philo->data->t0), philo->nb, F, philo->data->wutex);
	if (philo->data->nb_philo > 1)
	{
		if (philo->nb < philo->data->nb_philo)
			pthread_mutex_lock(philo->data->futex[philo->nb]);
		else
			pthread_mutex_lock(philo->data->futex[0]);
		if (check_go_on(philo))
			ft_printer(c_time(philo->data->t0), philo->nb, F, \
				philo->data->wutex);
		return (2);
	}
	return (1);
}

void	futex_unlock(t_philo *philo, int locked_fork_nb)
{
	pthread_mutex_unlock(philo->data->futex[philo->nb - 1]);
	if (locked_fork_nb == 2)
	{
		if (philo->nb < philo->data->nb_philo)
			pthread_mutex_unlock(philo->data->futex[philo->nb]);
		else
			pthread_mutex_unlock(philo->data->futex[0]);
	}
}

void	eating(t_philo *philo)
{
	int	locked_fork_nb;

	locked_fork_nb = futex_lock(philo);
	if (locked_fork_nb == 0)
		return ;
	if (locked_fork_nb == 2)
	{
		if (!check_go_on(philo))
			return (futex_unlock(philo, locked_fork_nb));
		ft_printer(c_time(philo->data->t0), philo->nb, E, philo->data->wutex);
		pthread_mutex_lock(philo->data->mealtex);
		philo->last_meal = c_time(philo->data->t0);
		philo->meal_nb -= 1;
		pthread_mutex_unlock(philo->data->mealtex);
	}
	ft_usleep(philo->data->tt_eat * 1000);
	futex_unlock(philo, locked_fork_nb);
	return (sleeping(philo));
}

void	sleeping(t_philo *philo)
{
	if (!check_go_on(philo))
		return ;
	ft_printer(c_time(philo->data->t0), philo->nb, S, philo->data->wutex);
	ft_usleep(philo->data->tt_sleep * 1000);
	return (thinking(philo));
}

void	thinking(t_philo *philo)
{
	if (!check_go_on(philo))
		return ;
	ft_printer(c_time(philo->data->t0), philo->nb, T, philo->data->wutex);
	return (eating(philo));
}
