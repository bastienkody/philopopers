/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:24:14 by bguillau          #+#    #+#             */
/*   Updated: 2023/09/13 14:24:17 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	fourchettes mutex (array) : malloc + init	*/
pthread_mutex_t	**init_futex(t_data *data)
{
	pthread_mutex_t	**futex;
	int				i;

	if (data->nb_philo == 0)
		return (NULL);
	futex = malloc((data->nb_philo + 1) * sizeof(pthread_mutex_t));
	if (!futex)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		futex[i] = malloc(1 * sizeof(pthread_mutex_t));
		if (!futex[i] || pthread_mutex_init(futex[i], NULL))
			return (free_futex(futex), NULL);
	}
	futex[i] = NULL;
	return (futex);
}

/*	writing mutex	*/
pthread_mutex_t	*init_wutex(void)
{
	pthread_mutex_t	*wutex;

	wutex = malloc(1 * sizeof(pthread_mutex_t));
	if (!wutex || pthread_mutex_init(wutex, NULL))
		return (free(wutex), NULL);
	return (wutex);
}

/*	go_on mutex	*/
pthread_mutex_t	*init_gutex(void)
{
	pthread_mutex_t	*gutex;

	gutex = malloc(1 * sizeof(pthread_mutex_t));
	if (!gutex || pthread_mutex_init(gutex, NULL))
		return (free(gutex), NULL);
	return (gutex);
}

/*	mutex for both meal_nb and last_meal	*/
pthread_mutex_t	*init_mealtex(void)
{
	pthread_mutex_t	*mealtex;

	mealtex = malloc(1 * sizeof(pthread_mutex_t));
	if (!mealtex || pthread_mutex_init(mealtex, NULL))
		return (free(mealtex), NULL);
	return (mealtex);
}
