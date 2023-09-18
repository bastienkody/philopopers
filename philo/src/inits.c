/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:18:46 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/08 16:18:49 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*init_all_mutexes(t_data *data)
{
	data->futex = init_futex(data);
	if (!data->futex)
		return (free(data), NULL);
	data->wutex = init_wutex();
	if (!data->wutex)
		return (end_free(NULL, data), NULL);
	data->gutex = init_gutex();
	if (!data->gutex)
		return (end_free(NULL, data), NULL);
	data->mealtex = init_mealtex();
	if (!data->mealtex)
		return (end_free(NULL, data), NULL);
	return (data);
}

t_data	*init_data(char **argv)
{
	t_data			*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->nb_philo = ft_atoi_noverflw(argv[0]);
	data->tt_die = ft_atoi_noverflw(argv[1]);
	data->tt_eat = ft_atoi_noverflw(argv[2]);
	data->tt_sleep = ft_atoi_noverflw(argv[3]);
	data->tt_think = (data->tt_die - data->tt_eat - data->tt_sleep) / 10 * 9;
	data->go_on = TRUE;
	if (argv[4])
		data->min_meals = ft_atoi_noverflw(argv[4]);
	else
		data->min_meals = -1;
	return (init_all_mutexes(data));
}

/* checks arg (++argv dans main) + calls init_data() */
t_data	*arg_to_data(int argc, char **argv)
{
	int		i;
	int		j;

	i = -1;
	if (argc < 5 || argc > 6)
		return (printf("%s\n", INV_ARG_NB), NULL);
	while (argv[++i])
	{
		if (*argv[i] == '-' || ft_atoi_noverflw(argv[i]) < 0)
			return (printf("One argument is negative, or overflowed\n"), NULL);
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("One argument with a non-digit value\n"), NULL);
		}
	}
	return (init_data(argv));
}

t_philo	**init_philo(t_data *data)
{
	t_philo	**philo;
	int		i;

	if (data->nb_philo == 0)
		return (NULL);
	philo = malloc((data->nb_philo + 1) * sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i] = malloc(1 * sizeof(t_philo));
		if (!philo[i])
			return (free_philo(philo), NULL);
		philo[i]->nb = i + 1;
		philo[i]->meal_nb = data->min_meals;
		philo[i]->last_meal = 0;
		philo[i]->t_id = 0;
		philo[i]->data = data;
	}
	philo[i] = NULL;
	return (philo);
}
