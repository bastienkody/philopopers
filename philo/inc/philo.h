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

/* const state */
# define EAT 0
# define SLEEP 1
# define THINK 2

/* typedef */
typedef struct s_philo
{
	int					nb;
	int					state;
	unsigned long int	t_id;
	int					last_meal;
	int					meal_nb;
}			t_philo;

typedef struct s_data
{
	int	nb_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	min_meals;
}			t_data;

/* inits */
t_data	*arg_to_data(int argc, char **argv);
t_philo	**init_philo(t_data *data);

/* free */
void	free_philo(t_philo **philo);
void	end_free(t_data *data, t_philo **philo);
void	phcreate_failure_mgmt(t_philo **philo, int i);

/* threading */
void	launcher(t_philo **philo);

/* utils */
int		ft_atoi_noverflw(const char *nptr);

/* print-debug */
void	print_data(t_data *data);
void	print_philo(t_philo **philo);

#endif
