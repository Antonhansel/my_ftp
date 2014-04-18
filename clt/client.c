/*
** main.c for main in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Mar 26 19:22:40 2014 ribeaud antonin
** Last update Sun Apr 13 15:07:14 2014 ribeaud antonin
*/

#include "client.h"

void	exit_client(t_ftp *ftp)
{
  close(ftp->s);
  exit (1);
}

void    send_message(char *str, t_ftp *ftp)
{
  write(ftp->s, str, strlen(str));
}

void	wait_client(t_ftp *ftp, int port, char *ip)
{
  int	error;

  error = connect(ftp->s, (const struct sockaddr *)
		  &ftp->sin, sizeof(ftp->sin));
  if (error == -1)
    {
      close(ftp->s);
      printf("Cant connect to server %s on port %i.\n", ip, port);
      exit(1);
    }
  if (send_username(ftp) == 1)
    {
      if (send_password(ftp) == 1)
	do_client(ftp);
    }
  exit_client(ftp);
  close(ftp->s);
}

void	init_client(char *ip, int port, t_ftp *ftp)
{
  int	error;

  ftp->pe = getprotobyname("TCP");
  ftp->s = socket(AF_INET, SOCK_STREAM, ftp->pe->p_proto);
  if (ftp->s == -1)
    my_error("Couldn't initialize sockets");
  ftp->sin.sin_family = AF_INET;
  ftp->sin.sin_port = htons(port);
  ftp->sin.sin_addr.s_addr = inet_addr(ip);
  wait_client(ftp, port, ip);
}

int	main(int argc, char **argv)
{
  t_ftp	ftp;

  if (argc == 3)
    init_client(argv[1], atoi(argv[2]), &ftp);
  else
    return (1);
  return (0);
}
