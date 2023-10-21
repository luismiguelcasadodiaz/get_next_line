/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/21 15:23:17 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE
#endif
/* gnl_join() joins preffix(buf) with suffix(raw). Both null terminated       */
/*                                                                            */
/* Buf can be empty. The function handles this situation.                     */
/*   A) do not request start in a position bigger than str's length           */
/*   B) do not request len character greater than the difference between      */
/*      str's length minus start position.                                    */
/* GETS                                                                       */
/*  *buf  : The preffix string.                                               */
/*  *raw  : the suffix  string.                                               */
/*                                                                            */
/* RETURNS                                                                    */
/*  preffix + suffix + '\0` is the normal behaviour                           */
/*  NULL     : When ENOMEM.                                                   */
/*                                                                            */
/* OPERATION                                                                  */
/*  set buf_size to zero and navigated it if exists to know its lenght        */
/*  set raw_size to zero and navigated it to know its lenght                  */
/*  allocate memory for resulting string                                      */
/*  use idx to index new, buf and raw. the index in raw is subtractes by      */
/*      buf size                                                              */
/*  copy buf over new                                                         */
/*  copy raw over new after buf                                               */
/*  free both raw and former buf                                              */
/*                                                                            */
char	*gnl_join(char *buf, char *raw)
{
	size_t	buf_size;
	size_t	raw_size;
	size_t	newbuf_size;
	size_t	idx;
	char	*newbuf;

	buf_size = 0;
	if (buf)
		while (buf[buf_size] != '\0')
			buf_size++;
	raw_size = 0;
	while (raw[raw_size] != '\0')
		raw_size++;
	newbuf_size = buf_size + raw_size + 1;
	newbuf = (char *)malloc(newbuf_size);
	if (newbuf == NULL)
		return (NULL);
	idx = 0;
	while (idx < (buf_size))
	{
		newbuf[idx] = buf[idx];
		idx++;
	}
	while ((idx - buf_size) < raw_size)
	{
		newbuf[idx] = raw[idx - buf_size];
		idx++;
	}
	newbuf[idx] = '\0';
	free(buf);
	buf = NULL;
	free(raw);
	raw = NULL;
	return (newbuf);
}

/* gnl_substr () returns a substring of size len from a string starting in    */
/* the start position                                                         */
/*                                                                            */
/* It is a simplification form FT_substr. Calling function is responsible for */
/*   A) do not request start in a position bigger than str's length           */
/*   B) do not request len character greater than the difference between      */
/*      str's length minus start position.                                    */
/* GETS                                                                       */
/*  *str  : The string to extract from                                        */
/*  start : Substring initial position.                                       */
/*  len   : Size of string to return                                          */
/*                                                                            */
/* RETURNS                                                                    */
/*  Substring: correct behavior.                                              */
/*  NULL     : When ENOMEM.                                                   */
/*                                                                            */
static char	*gnl_substr(char *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	idx;

	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		sub[idx] = str[start + idx];
		idx++;
	}
	sub[idx] = '\0';
	return (sub);
}

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
	if (read_raw != NULL)
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
char	*read_to_buff(int fd, char	*read_buf)
{
	ssize_t		read_bytes;
	char		*read_raw;

	read_buffer_size(fd, &read_raw, &read_bytes);
	if (read_bytes <= 0)
		return (NULL);
	return (gnl_join(read_buf, read_raw));
}

short	buff_analisis(char	**read_buf, char	**line)
{
	char		*read_buf_part1;
	char		*read_buf_part2;
	ssize_t		idx;
	ssize_t		idx_ret;
	short		found; 

	found = 0;
	idx = 0;
	while (read_buf[0][idx] != '\0' && read_buf[0][idx] != '\n')
		idx++;
	if (read_buf[0][idx] == '\n')
	{
		idx_ret = idx + 1;
		read_buf_part1 = gnl_substr(*read_buf, 0, idx_ret);
		found = 1;
		while (read_buf[0][idx] != '\0')
			idx++;
		read_buf_part2 = gnl_substr(*read_buf, idx_ret, (idx - (idx_ret)));
		free(*read_buf);
		*read_buf = read_buf_part2;
		*line = read_buf_part1;
		found = 1;
	}
	else
		*line = NULL;
	return (found);
}

char	*get_next_line(int fd)
{
	static char	*read_buf;
	char		*line;
	short		found;

	found = 0;
	while (!found)
	{
		if (read_buf == NULL)
		{
			read_buf = read_to_buff(fd, read_buf);
			if (read_buf)
				found = buff_analisis(&read_buf, &line);
		}
		else
		{
			found = buff_analisis(&read_buf, &line);
			if (!found)
				read_buf = read_to_buff(fd, read_buf);
		}
	}
	return (line);
}
