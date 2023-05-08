/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:22:51 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/05 16:28:58 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* libraries */
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/* const */

/* typedef */
typedef struct s_philo
{
	int	nb;
	int	last_meal;
	int	meal_nb;
}			t_philo;

typedef struct s_data
{
	int	nb_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	min_meals;
}			t_data;

/* proto utils */
int	ft_atoi_noverflw(const char *nptr);

/* proto print-debug */
void	print_data(t_data *data);

#endif
