/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:24:54 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/08 14:25:17 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_data(t_data *data)
{
	if (!data)
		printf("data is NULL\n");
	printf("\tT_DATA\n");
	printf("nb_philo = %i\n", data->nb_philo);
	printf("tt_die = %i\n", data->tt_die);
	printf("tt_eat = %i\n", data->tt_eat);
	printf("tt_sleep = %i\n", data->tt_sleep);
	printf("min_meals = %i\n", data->min_meals);
	printf("-------------------------\n");
}

void	print_philo(t_philo **philo)
{
	int	i;

	if (!philo)
		printf("philo is NULL\n");
	i = 0;
	printf("\tT_PHILO\n");
	while (philo[i])
	{
		printf("philo[%i].nb = %i\n", i, philo[i]->nb);
		//printf("philo[%i].last_meal = %i", i, philo[i]->last_meal);
		printf("philo[%i].meal_nb = %i\n", i, philo[i]->meal_nb);
		i++;
	}
	printf("-------------------------\n");
}
