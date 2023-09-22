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

/*	destroy then free	*/
void	free_futex(pthread_mutex_t **futex)
{
	int	i;

	if (!futex)
		return ;
	i = -1;
	while (futex[++i])
	{
		pthread_mutex_destroy(futex[i]);
		free(futex[i]);
	}
	free(futex);
}

void	end_free(t_philo **philo, t_data *data)
{
	if (data->futex)
		free_futex(data->futex);
	if (data->wutex)
	{
		pthread_mutex_destroy(data->wutex);
		free(data->wutex);
	}
	if (data->gutex)
	{
		pthread_mutex_destroy(data->gutex);
		free(data->gutex);
	}
	if (data->mealtex)
	{
		pthread_mutex_destroy(data->mealtex);
		free(data->mealtex);
	}
	if (philo)
		free_philo(philo);
	if (data)
		free(data);
}

/*	stop simul : go_on=False, so no new action for created philo
	detach all already created philo : no need to join them
	all philo will still be freed (via end_free in main)
	set t_id of detach thread to 0 (most prob unecessary)
*/
void	phcreate_failure_mgmt(t_philo **philo, int i)
{
	int	j;

	turn_go_on_to_false(*philo);
	printf("%s %i. %s", FAILED, i, DETACH);
	j = -1;
	while (philo[++j])
	{
		if (philo[j]->t_id)
		{
			if (pthread_detach(philo[j]->t_id) != 0)
				printf("%s %i\n", DETACH_FAILED, j);
			philo[j]->t_id = 0;
		}
	}
}
