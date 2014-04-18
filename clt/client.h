/*
** client.h for client in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 14:02:10 2014 ribeaud antonin
** Last update Fri Apr 11 22:38:33 2014 ribeaud antonin
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <netdb.h>
# include <error.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/types.h>
# define _XOPEN_SOURCE
# include <crypt.h>

#define BUFF_SIZE	4096

typedef struct		s_ftp
{
  struct protoent	*pe;
  struct sockaddr_in	sin;
  struct sockaddr_in	sin_client;
  int			filesize;
  char			*homepwd;
  int			s;
  int			cs;
}			t_ftp;
/***
 **get_file.c
 **/
void	transer_file(FILE *, t_ftp *);
int	get_filename(t_ftp *);
void	fail_local(t_ftp *, char *);
void	get_file(char *, t_ftp *);
/***
 **send_file.c
 **/
void	trans_file(t_ftp *, char **);
void	send_file(t_ftp *, int);
int	bad_file(char *);
int     open_fd(t_ftp *, char *);
/***
 **str_to_wordtab.c
 **/
int	word_count(char *, char);
char	**my_str_to_wordtab2(char *, char, char **);
char	**my_str_to_wordtab(char *, char);
/***
 **password.c
 **/
int	send_password(t_ftp *);
int	send_username(t_ftp *);
/***
 **get_file2.c
 **/
char	*getfilename(char *);
FILE	*open_file(char *);
/***
 **client.c
 **/
void	exit_client(t_ftp *);
void    send_message(char *, t_ftp *);
void	wait_client(t_ftp *, int, char *);
void	init_client(char *, int, t_ftp *);
/***
 **basic.c
 **/
void	read_message(t_ftp *);
void	do_client(t_ftp *);
void	do_simplecommand(t_ftp *, char*);

#endif /*_CLIENT_H_*/
