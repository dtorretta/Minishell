/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:04:06 by miguandr          #+#    #+#             */
/*   Updated: 2024/03/25 21:42:05 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_count_hexa(unsigned int num)
{
	int	count;

	count = 0;
	while (num)
	{
		num /= 16;
		count++;
	}
	return (count);
}

void	ft_print_hexa(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_print_hexa(num / 16, format);
		ft_print_hexa(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + 48);
		else
		{
			if (format == 'x')
				ft_putchar(num - 10 + 'a');
			if (format == 'X')
				ft_putchar(num - 10 + 'A');
		}
	}
}

int	ft_puthexa(unsigned int num, const char type)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_print_hexa(num, type);
	return (ft_count_hexa(num));
}
