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
