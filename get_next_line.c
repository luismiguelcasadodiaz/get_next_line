/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/24 13:32:17 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE
#endif
/* gnl_read_buffer_size() returns thru parameters passed by reference the     */
/* number of bytes read from a file descriptor and a null-terminated string   */
/* holding read bytes                                                         */
/*                                                                            */
/* GETS                                                                       */
/*  fd    : The file descriptor to read from.                                 */
/*  **read_raw : Holder to return a null-terminated string wiht read bytes    */
/*  *read_bytes: Holder to return amount of bytes read.                       */
/*                                                                            */
/* RETURNS                                                                    */
/*  inside **read_raw:                                                        */
/*    null-terminated-string wiht read butes: normal behaviour                */
/*    NULL     : When ENOMEM, end  of file, fd read error                     */
/*  inside *read_bytes:                                                       */
/*    -1 o 0 when error.                                                      */
/*    amount of bytes read: normal behaviour                                  */
/*                                                                            */
static void	read_buffer_size(int fd, char **read_raw, ssize_t *read_bytes)
{
	*read_raw = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*read_raw == NULL)
		*read_bytes = -1;
	else
	{
		*read_bytes = read(fd, *read_raw, BUFFER_SIZE);
		if (*read_bytes <= 0)
		{
			free(*read_raw);
			*read_raw = NULL;
		}
		else
			read_raw[0][*read_bytes] = '\0';
	}
}

/* read_to_buff()  joins existing buffer and read bytes from file descriptor  */
/*                                                                            */
/* GETS                                                                       */
/*  fd : The file descriptor to read from                                     */
/*  **read_buf : A passed by reference buffer to save read bytes in.          */
/*                                                                            */
/* RETURNS                                                                    */
/*  The number of bytes read. A positive integer >0 normal behaviour.         */
/*  Zero when end of file and no more bytes to read remain in fd.             */
/*  negative when other problems wiht fd.                                     */
/*                                                                            */
/* OPERATION                                                                  */
/*                                                                            */
/* Automatic Variables                                                        */
/*  read_bytes  keep numer of read bytes from file descriptor.                */
/*  *read_raw to keep read bytes from file descriptor.                        */
/*                                                                            */
/*  Read_buffer_size returns fill in both automatic variables.                */
/*                                                                            */
/*  Only when there are read bytes, read_raw buffer joins to read_buf.        */
/*                                                                            */
/*  The function returns read_bytes.                                          */
/*                                                                            */
ssize_t	read_to_buff(int fd, char	**read_buf)
{
	ssize_t		read_bytes;
	char		*read_raw;
	char		*aux_buf;

	read_buffer_size(fd, &read_raw, &read_bytes);
	if (read_bytes > 0)
	{
		aux_buf = gnl_join(*read_buf, read_raw);
		free(*read_buf);
		*read_buf = aux_buf;
		free(read_raw);
		read_raw = NULL;
	}
	return (read_bytes);
}

short	buff_analisis(char	**read_buf, char	**line)
{
	char		*read_buf_part2;
	ssize_t		idx;
	ssize_t		idx_ret;
	short		found;

	*line = NULL;
	found = 0;
	if (*read_buf == NULL)
		return (found);
	idx = 0;
	while (read_buf[0][idx] != '\0' && read_buf[0][idx] != '\n')
		idx++;
	if (read_buf[0][idx] == '\n')
	{
		idx_ret = idx + 1;
		*line = gnl_substr(*read_buf, 0, idx_ret);
		found = 1;
		while (read_buf[0][idx] != '\0')
			idx++;
		read_buf_part2 = gnl_substr(*read_buf, idx_ret, (idx - (idx_ret)));
		free(*read_buf);
		*read_buf = read_buf_part2;
		found = 1;
	}
	return (found);
}

void	buff_flush(char **read_buf, char **line)
{
	size_t	i;

	if (*read_buf == NULL)
	{
		*line = NULL;
		return ;
	}
	i = 0;
	while (read_buf[0][i] != '\0')
		i++;
	*line = (char *)malloc(i + 1);
	if (*line != NULL)
	{
		i = 0;
		while (read_buf[0][i] != '\0')
		{
			line[0][i] = read_buf[0][i];
			i++;
		}
		line[0][i] = '\0';
	}
	free(*read_buf);
	*read_buf = NULL;
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
char	*get_next_line(int fd)
{
	static char	*read_buf;
	ssize_t		read_bytes;
	char		*line;
	short		found;
	short		file_end;

	found = 0;
	file_end = 0;
	while (!found && !file_end)
	{
		found = buff_analisis(&read_buf, &line);
		if (!found)
		{
			read_bytes = read_to_buff(fd, &read_buf);
			if (read_bytes == 0)
			{
				buff_flush(&read_buf, &line);
				file_end = 1;
				free(read_buf);
				read_buf = NULL;
			}
			if (read_bytes == -1)
			{
				file_end = 1;
				free(read_buf);
				read_buf = NULL;
				free(line);
				line = NULL;
			}
		}
	}
	return (line);
}
