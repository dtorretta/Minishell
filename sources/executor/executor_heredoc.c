/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:27:45 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/19 23:25:32 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

char	*generate_filename(void)
{
	static int	i;
	char		*file_num;
	char		*file_name;

	i = 0;
	file_num = ft_itoa(i++);
	file_name = ft_strjoin("/tmp/heredoc_", file_num);
	free(file_num);
	return (file_name);
}
