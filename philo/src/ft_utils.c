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
	int		sign;
	int		res;
	int		old_res;

	sign = 1;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	res = 0;
	old_res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr++ - '0');
		if (res < old_res)
			return (-1);
		old_res = res;
	}
	return (res * sign);
}

/*	wutex lock + print philo msg
	printf for now. if too long i'd try itoa + write	*/
void	ft_printer(unsigned long int time, int philo_nb, char *msg,
	pthread_mutex_t *wutex)
{
	pthread_mutex_lock(wutex);
	printf("%lu %i %s\n", time, philo_nb, msg);
	pthread_mutex_unlock(wutex);
}
