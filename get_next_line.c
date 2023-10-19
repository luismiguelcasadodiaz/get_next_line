/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/19 14:58:23 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	read_buffer_size(int fd, char **read_raw, size_t *read_bytes)
{
	*read_raw = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_raw == NULL)
		return (NULL);
	read_bytes = read(fd, *read_raw, BUFFER_SIZE);
	if (read_bytes == 0)
	{
		free(*read_raw);
		*read_raw = NULL;
	}
	else
		*read_raw[read_bytes]= '\0';
}

/* get_next_line() returns a line from a file descriptor.                     */
/*                                                                            */
/* GETS                                                                       */
/*  fd : The file descriptor to read from                                     */
/*                                                                            */
/* RETURNS                                                                    */
/*  Read line: correct behavior.                                              */
/*  NULL     : there is nothing else to read, or an error occurred            */
/*                                                                            */
/* OPERATION                                                                  */
/*                                                                            */
/* Automatic Variables                                                        */
/*  read_raw to keep bytes as they come from file.                            */
/*  read_buf to keep read bytes not yet delivered.                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*  If i have not bytes to deliver (read_buf == NULL) then i read more        */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*   static int	previous_fd;                                                  */
/*	if (previous_fd == fd)                                                    */
/*		write(1, &"same\n", 6);                                               */
/*	else                                                                      */
/*		write(1, &"different\n", 11);                                         */
/*	previous_fd = fd;                                                         */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
char	*get_next_line(int fd)
{
	size_t			read_bytes;
	char			*read_raw;
	static char		*read_buf;
	short			found_nl;
	size_t			idx;

	found_nl = 0;

	while (!found_nl)
	{
		if (read_buf == NULL)
		{
			read_buffer_size(fd, &read_raw, &read_bytes);
			idx = 0;
			while (read_raw[idx] != '\0' && read_raw[idx++] != '\n')
				;	
		if (idx == read_bytes)
			read_buf = read_raw;
		}
		else
		{
		}

	if (read_bytes == 0)
		return (NULL);
	return (read_buf);
}
