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
	if (!(philo->nb & 1))
		eating(philo);
	else 
		thinking(philo);
	return (NULL);
}

/*	for odd threads not to overrun even threads at forks picking 1st meal
	the lower the numbers the bigger the delay (max_philo=200 is protected)	*/
void	parity_launch_delay(t_philo *philo)
{
	const int	delay = MAX_PHILO - philo->data->nb_philo;

	if (delay > 0)
		return (ft_usleep(delay, philo));
	ft_usleep(1, philo);
}

/*	parity:	0 -> even ;	1 -> odd	*/
int	half_launcher(t_philo **philo, t_bool parity)
{
	pthread_t	thread;
	int			i;

	i = -1;
	while (philo[++i])
	{
		if ((i + 1) % 2 != parity)
			continue ;
		if (pthread_create(&thread, NULL, &routine, philo[i]))
			return (phcreate_failure_mgmt(philo, i + 1), 0);
		else
			philo[i]->t_id = thread;
	}
	return (1);
}

/*	launch evens then odds, checkers, join threads at end	*/
void	simulator(t_philo **philo, int argc)
{
	int	i;

	if (half_launcher(philo, 0) == 0)
		return ;
	parity_launch_delay(*philo);
	if (half_launcher(philo, 1) == 0)
		return ;
	while (TRUE)
	{
		ft_usleep(1000, *philo);
		if (argc == 6 && !check_meal(philo))
			break ;
		if (!check_death(philo))
			break ;
	}
	i = -1;
	while (philo[++i])
		if (pthread_join(philo[i]->t_id, NULL))
			printf("Error joining t_id %lu\n", philo[i]->t_id);
}
