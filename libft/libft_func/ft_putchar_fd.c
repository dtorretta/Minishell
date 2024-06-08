/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:02:21 by miguandr          #+#    #+#             */
/*   Updated: 2024/03/25 19:57:57 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*ft_putchar_fd -- write character c on a specified file descriptor*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
