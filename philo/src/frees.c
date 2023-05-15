/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:08:52 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/08 17:09:12 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_philo(t_philo **philo)
{
	int	i;

	if (!philo)
		return ;
	i = -1;
	while (philo[++i])
		free(philo[i]);
	free(philo);
}

void	end_free(t_data *data, t_philo **philo)
{
	if (data)
		free(data);
	if (philo)
		free_philo(philo);
}

/*	detach all philo
	set t_id of detach thread to 0
	philo with t_id of 0 wont be executed in the simulation */
void	phcreate_failure_mgmt(t_philo **philo, int i)
{
	int	j;

	printf("phtread_create failed on philo %i. Program exiting\n", i);
	j = -1;
	while (philo[++j])
	{
		if (philo[j]->t_id)
		{
			if (pthread_detach(philo[j]->t_id) != 0)
				printf("phtread_detach also failed on philo %i...\n", j);
			philo[j]->t_id = 0;
		}
	}
}
