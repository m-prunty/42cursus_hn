/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/26 20:13:03 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*ft_gnlnew(void *content)
{
	t_gnl	*new;

	new = (t_gnl *)malloc(sizeof(t_gnl));
	if (!new)
		return (NULL);
	new->content = ft_calloc(CHUNK_SIZE, 1);
	new->n = ft_strlen((char *)content);
	ft_memcpy(new->content, content, new->n);
	//new->n = ft_strlen(new->content);
	new->next = NULL;
	return (new);
}

void	ft_gnlclear(t_gnl **gnlbuf)
{
	t_gnl	*tmp;

	while (*gnlbuf)
	{
		tmp = ((*gnlbuf)->next);
		free((*gnlbuf)->content);
		(*gnlbuf)->content = NULL;
		free(*gnlbuf);
		*gnlbuf = tmp;
	}
	//free(gnlbuf);
	gnlbuf = NULL;
}

char	*return_nl(t_gnl **gnlbuf, char ptr[])
{
	
	t_gnl	*tmp;
	int		n_nl;
	char	*nl;
	int		n;

	n = 0;
	tmp = *gnlbuf;
	nl = ft_memchr(tmp->content, '\n', tmp->n);
	while (!nl && tmp->next && ++n)
	{
		tmp = tmp->next;
		nl = ft_memchr(tmp->content, '\n', tmp->n);
	}	
	if (!nl)
		nl = tmp->content + tmp->n;
	n_nl = (nl - (char *)tmp->content) + ((n) * CHUNK_SIZE) + 1;
	ft_bzero(ptr, BUFFER_SIZE + 1);
	ft_memmove(ptr, nl + 1, tmp->n - (n_nl % CHUNK_SIZE));
	nl = ft_calloc(n_nl  + 1, 1);
	if (!nl)
		return (ft_gnlclear(gnlbuf), NULL);
	tmp = *gnlbuf;
	while (n_nl > 0)
	{
		ft_memcpy(nl, tmp->content, tmp->n - ((n_nl < (int)tmp->n) * (tmp->n - n_nl)));
		n_nl -= (tmp->n - ((n_nl < (int)tmp->n) * (tmp->n - n_nl)));
		if (tmp->next)
			tmp = tmp->next;
	}
	ft_gnlclear(gnlbuf);
	return (nl);
}

int	add_to_nl(t_gnl **gnlbuf, char *buf, int fd)
{
	t_gnl	*tmp;
	int	nread;

	*gnlbuf= ft_gnlnew(buf);
	tmp = *gnlbuf;	
	nread = tmp->n;
	while (!ft_memchr(tmp->content + (tmp->n - nread), '\n', nread) )
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == 0)
			return (1);
		else if (nread < 0)
			return (0);
		if (tmp->n + BUFFER_SIZE >= CHUNK_SIZE)
		{
			tmp->next = ft_gnlnew(buf);
			tmp = tmp->next;
		}
		else
		{
			ft_memcpy(tmp->content + tmp->n, buf, nread);
			tmp->n += nread;
		}
	}
	return (1);	
}

char *get_next_line(int fd)
{
	static char	ptr[BUFFER_SIZE + 1] = {0};
	t_gnl		*gnlbuf;
//	char		*buf;


	//gnlbuf = (t_gnl *)ft_calloc(sizeof(t_gnl) , 1);
	if (!add_to_nl(&gnlbuf, ptr, fd))
		return (NULL);
	if (*(char *)(gnlbuf->content))
		return (return_nl(&gnlbuf, ptr));
	return (ft_gnlclear(&gnlbuf), NULL);

	//buf = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	//ft_memcpy(buf, ptr, BUFFER_SIZE);


}



//int calloc_help(char *str, )
/*
   void *free_null(char **ptr)
   {
   free(*ptr);
 *ptr = NULL;
 return (NULL);
 }
 char *clean_return(char ptr[], char **tmp)
 {
 char    *nl;
 char    *line;
 size_t  len;
 size_t  tail_len;
: nl = ft_memchr(*tmp, '\n', ft_strlen(*tmp));
 if (nl)
 len = (nl - *tmp) + 1;
 else
 len = ft_strlen(*tmp);

 line = malloc(len + 1);
 if (!line)
 return (NULL);

 ft_memcpy(line, *tmp, len);
 line[len] = '\0';
 tail_len = ft_strlen(*tmp + len);
 ft_memmove(ptr, *tmp + len, tail_len);
 ptr[tail_len] = '\0';
 free_null(tmp);
 return (line);
 }

 int add_to_stat(char **tmpbuf, char *buf, int *nread)
 {
 size_t	n;
 char	*tmp;

 n = 0;
 if (*tmpbuf)
 n = ft_strlen(*tmpbuf);
 tmp = ft_calloc(n + *nread + 1, sizeof(char));
 if (!tmp)
 {
 *nread = 0;
 return (0);
 }
 ft_memcpy(tmp, *tmpbuf, n);
 ft_memcpy(tmp + n, buf, *nread);
 tmp[n + *nread] = '\0';
 if (n)
 free_null(tmpbuf);
 *tmpbuf = tmp;
 return (1);
 }

 char *get_next_line(int fd)
 {
 static char ptr[BUFFER_SIZE + 1] = {0};
 char        *buf;
 char        *tmpbuf;
 int         nread;

 buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
 if (!buf)
 return (NULL);
 tmpbuf = "";//ft_calloc(ft_strlen(ptr) + 1, sizeof(char));
 nread = 1;
 if (ptr[0])
 {
 nread = ft_strlen(ptr);
ft_memcpy(buf, ptr, ft_strlen(ptr));
}
while ((!ft_memchr(tmpbuf, '\n', ft_strlen(tmpbuf)) && nread > 0) || ptr[0])
{ 
	if (!ptr[0])
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		nread = read(fd, buf, BUFFER_SIZE);
	}
	else
		ft_bzero(ptr, BUFFER_SIZE + 1);
	if (nread > 0 && add_to_stat(&tmpbuf, buf, &nread))
		;
	else if (nread < 0)
		return (free_null(&buf), NULL);
}
free_null(&buf);
if (*tmpbuf)
	return ( clean_return(ptr, &tmpbuf));
	return ( NULL);
	}
*/

/*
   char	*clean_return(char ptr[], char *buf)
   {	char	*nl;
   char	*sub;
   size_t	n;

   nl = ft_strchr(buf, '\n');
   if (nl)
   n = nl - buf + 1;
   else
   n = ft_strlen(buf);
   sub = ft_calloc(sizeof(char), n  + 1);
   if (!sub)
   return (NULL);
   ft_memcpy(sub, buf, n);
   ft_memmove(ptr, buf + n, ft_strlen(buf + n));		
   ptr[ft_strlen(buf + n)] = '\0';
   free(buf);
   return (sub);
   }

   int	add_to_stat(char **tmpbuf, char **buf, int *nread)
   {
   int		n;
   char	*tmp;

   n = 0;
   if (*tmpbuf != *buf)
   n = ft_strlen(*tmpbuf);
   tmp = (char *)ft_calloc((n + *nread + 1), sizeof(char));
   if (!tmp)
   {
 *nread = -1;
 return (0);
 }

 ft_memcpy(tmp, *tmpbuf, n);
 ft_memcpy(tmp + n, *buf, *nread);
 tmp[n + *nread] = '\0';

 if (*tmpbuf != *buf)
 free(*tmpbuf);
 *tmpbuf = tmp;
 return (1);
 }

 char	*get_next_line(int fd)
 {
 static char	ptr[BUFFER_SIZE + 1] = {0};
 char		*buf;
 char		*tmpbuf;
 int			nread;

 nread = -1;
 tmpbuf = NULL;
 buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
 if (!buf)
 return (NULL);
 while ((!ptr[0] && !ft_strchr(buf, '\n')) || ft_strchr(ptr ) && nread)
 {
 ft_bzero(buf, BUFFER_SIZE);
 nread = read(fd, buf, BUFFER_SIZE);
 if (!tmpbuf)
 tmpbuf = buf;
 if (nread >= 1 && add_to_stat(&tmpbuf, &buf, &nread))
 ;
 else if (nread < 0)
 return (free_null(&buf),  NULL);
 }
 if (!buf[0] && ptr[0])
 {
tmpbuf = buf;
ft_memcpy(tmpbuf, ptr, ft_strlen(ptr));
}
return (clean_return(ptr, tmpbuf));
}*/

/*
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}


void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}


void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = ((*lst)->next);
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}


void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}


void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}


t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = (lst->next);
	return (lst);
}


t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*content;

	if(!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{	
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			del(content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}


t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}


int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && ++i)
		lst = (lst->next);
	return (i);
}
*/
