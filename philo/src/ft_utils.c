/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:22:23 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/05 15:57:04 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	- only digits (except leading '-')
	- nb < 0 returned to arg_checker are reco as errors
	- returns -1 if overflow	*/
int	ft_atoi_noverflw(const char *nptr)
{
	int		res;
	int		old_res;

	if (*nptr == '-')
		return (-1);
	res = 0;
	old_res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr++ - '0');
		if (res < old_res)
			return (-1);
		old_res = res;
	}
	return (res);
}

const char	*apply_color(int philo_nb)
{
	const char	*color[8] = {"\033[31m", "\033[32m", "\033[33m", \
		"\033[34m", "\033[35m", "\033[36m", "\033[37m", NULL};

	return (color[philo_nb % 7]);
}

void	ft_printer(unsigned long int time, int philo_nb, char *msg,
	pthread_mutex_t *wutex)
{
	time /= 1000;
	pthread_mutex_lock(wutex);
	printf("%s%lu %i %s\033[0m\n", apply_color(philo_nb), time, philo_nb, msg);
	pthread_mutex_unlock(wutex);
}
