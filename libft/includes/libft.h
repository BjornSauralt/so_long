/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:24:18 by mgarsaul          #+#    #+#             */
/*   Updated: 2024/10/14 12:01:25 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

//1ERE PARTIE

int		ft_isprint(int car);
int		ft_isalpha(int car);
int		ft_isalnum(int car);
int		ft_isascii(int car);
int		ft_isdigit(int car);
void	*ft_memchr(const void *arr, int search, size_t size);
void	*ft_memset(void *arr, int val, size_t size);
char	*ft_strchr(const char *str, int car);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strrchr(char *str, int car);
int		ft_tolower(int car);
int		ft_toupper(int car);
int		ft_memcmp(const void *arr1, const void *arr2, size_t size);
void	ft_bzero(void *arr, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_atoi(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t size);
void	*ft_calloc(size_t elt, size_t size);
char	*ft_strdup(const char *src);

//2EME PARTIE

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_putnbr_fd(int n, int fd);

//BONUS

#endif
