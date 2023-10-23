/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:58:39 by luicasad          #+#    #+#             */
/*   Updated: 2023/10/23 13:28:23 by luicasad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE
#endif

size_t	gnl_strlen(char	*s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			i++;
	return (i);
}

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
/*  preffix + suffix + null-terminator is the normal behaviour                */
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
	size_t	idx;
	char	*newbuf;

	buf_size = gnl_strlen(buf);
	raw_size = gnl_strlen(raw);
	newbuf = (char *)malloc(buf_size + raw_size + 1);
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
char	*gnl_substr(char *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	idx;

	if (len == 0)
		return (NULL);
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
