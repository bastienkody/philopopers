/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:17:03 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/05 16:30:35 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi_noverflw(argv[0]);
	data->tt_die = ft_atoi_noverflw(argv[1]);
	data->tt_eat = ft_atoi_noverflw(argv[2]);
	data->tt_sleep = ft_atoi_noverflw(argv[3]);
	if (argv[4])
		data->min_meals = ft_atoi_noverflw(argv[4]);
	else
		data->min_meals = -1; 
	return (data);
}

int	arg_to_data(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	if (argc < 5 || argc > 6)
		return (write(2, "Arg nb pb\n", 10), 1);
	while (argv[++i])
	{
		if (*argv[i] == '-' || ft_atoi_noverflw(argv[i]) < 0)
			return (write(2, "Arg < 0 (or int over/under flow)\n", 33), 1);
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (write(2, "Arg with non digit val\n", 23), 1);
		}
	}
	data = init_data(argv);
	if (!data)
		return (1);
	return (0);
}

t_philo	*init(char **argv)
{
	t_philo	*philo;

	philo = malloc(ft_atoi_noverflw(argv[0]) * sizeof(t_philo));
	if (!philo)
		return (NULL);
	return (philo);
}

int	main(int argc, char **argv)
{
	static t_philo	*philo = NULL;
	static t_data	*data = NULL;

	if (arg_to_data(argc, ++argv, data))
		return (1);
	philo = init(argv);
	if (!philo)
		return (2);
	print_data(data);
}
