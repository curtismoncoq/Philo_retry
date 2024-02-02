/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:11:47 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/17 18:14:19 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(void)
{
	struct timeval	xtv;

	gettimeofday(&xtv, NULL);
	return ((xtv.tv_sec * 1000) + (xtv.tv_usec / 1000));
}
