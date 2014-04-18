/*
** ftp.h for frp in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Mar 26 19:22:47 2014 ribeaud antonin
** Last update Sun Apr 13 15:23:53 2014 ribeaud antonin
*/

#ifndef _FTP_H_
# define _FTP_H_

#define _BSD_SOURCE
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <fcntl.h>
# include <signal.h>
# include <error.h>
# include <string.h>
# include <arpa/inet.h>

#define WELCOME	"[-] Welcome on Apollo's FTP\n[*] Please enter your password\n"
#define PASSOK  "Passwords matches, client @%s accepted!\n"
#define BUFF_SIZE 4096

typedef struct		s_ftp
{
  struct protoent	*pe;
  struct sockaddr_in	sin;
  struct sockaddr_in	sin_client;
  int			s;
  int			cs;
  char			*pwd;
  char			*homepwd;
  char			*password;
  char			*username;
  char			*ipclient;
  int			filesize;
}			t_ftp;

/***
 **server.c
 ***/
void	send_message(char *, t_ftp *);
void	read_client(t_ftp *);
void	loop_server(t_ftp *);
/***
 **commands.c
 ***/
void	my_delete(t_ftp *, char **);
void	my_pwd(t_ftp *);
void	my_ls(t_ftp *);
void	exec_cmd(t_ftp *, char *);
void	check_args(t_ftp *, char **, char *);
/***
 **error.c
 ***/
void	my_error(char *);
/***
 **get_file.c
 ***/
void	fail_local(t_ftp *, char *);
void	transfer_file(FILE *, t_ftp *);
int	get_size(t_ftp *);
void	trans_file(char *, t_ftp *);
/***
 **get_file2.c
 ***/
char	*getfilename(char *);
FILE	*open_file(char *);
/***
 **init.c
 ***/
int	get_infos(t_ftp *);
void	init_server(int, t_ftp *);
int	get_home(t_ftp *);
int	init_protocol(int, t_ftp *);
int	xbind(t_ftp *);
/***
 **passwordc
 ***/
int	read_user(t_ftp *);
int	read_password(t_ftp *);
int	send_ok(t_ftp *);
int	ok_password(t_ftp *);
/***
 **send_file.c
 ***/
int	open_fd(t_ftp *, char *);
void	send_file(t_ftp *, int);
void	get_file(t_ftp *, char **);
int	bad_file(char *);

/***
 **send_file2.c
 ***/
void	transfer_failed(t_ftp *, int);
void	send_size(t_ftp *);
/***
 **signal.c
 ***/
void	my_sighandler(int);
/***
 **str_to_wordtab.c
 ***/
int	word_count(char *, char);
char	**my_str_to_wordtab2(char *, char, char **);
char	**my_str_to_wordtab(char *, char);
/***
 **chdir.c
 ***/
void	my_chdir(t_ftp *, char *);
void	test_chdir(t_ftp *, char *, char *);

#endif /*_FTP_H_*/
