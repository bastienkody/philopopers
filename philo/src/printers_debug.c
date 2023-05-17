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
	printf("-------------------------\n");
	printf("\tT_DATA\n");
	printf("nb_philo = %i\n", data->nb_philo);
	printf("tt_die = %i\n", data->tt_die);
	printf("tt_eat = %i\n", data->tt_eat);
	printf("tt_sleep = %i\n", data->tt_sleep);
	printf("tt_think = %i\n", data->tt_think);
	printf("min_meals = %i\n", data->min_meals);
	printf("-------------------------\n");
}

void	print_philo(t_philo **philo)
{
	int	i;

	if (!philo)
		printf("philo is NULL\n");
	i = 0;
	printf("-------------------------\n");
	printf("\tT_PHILO\n");
	while (philo[i])
	{
		printf("PHILO %i (i=%i)\n", philo[i]->nb, i);
		printf(".th_id = %lu\n", philo[i]->t_id);
		//printf(".last_meal = %i", philo[i]->last_meal);
		//printf(".state = %i", philo[i]->last_meal);
		printf(".meal_nb = %i\n", philo[i]->meal_nb);
		i++;
	}
	printf("-------------------------\n");
}

void	print_futex(pthread_mutex_t **futex)
{
	int	i;

	if (!futex)
		return ;
	i = -1;
	while (futex[++i])
		printf("mutex %i :%p\n", i + 1, futex[i]);
}
