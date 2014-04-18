/*
** basic.c for basic in /home/apollo/rendu/PSU_2013_myftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 11 20:25:49 2014 ribeaud antonin
** Last update Fri Apr 11 23:27:27 2014 ribeaud antonin
*/

#include "client.h"

void		read_message(t_ftp *ftp)
{
  int		cont;
  size_t	len;
  char		buf[BUFF_SIZE];

  cont = 1;
  len = 0;
  memset(buf, 0, sizeof(buf));
  while (cont == 1 && (len = read(ftp->s, buf, sizeof(buf))) > 0)
    {
      write(1, buf, strlen(buf));
      if (len < sizeof(buf))
	{
	  cont = 0;
	  if (buf[len - 1] != '\n')
	    printf("\n");
	}
      memset(buf, 0, sizeof(buf));
    }
}

void	do_simplecommand(t_ftp *ftp, char *buf)
{
  write(ftp->s, buf, strlen(buf));
  read_message(ftp);
}

void	do_client(t_ftp *ftp)
{
  char	buf[BUFF_SIZE];
  int	len;
  int	exit;

  exit = 1;
  while (exit != 0)
    {
      memset(buf, 0, sizeof(buf));
      write(1, "FTP> ", 6);
      len = read(0, buf, sizeof(buf));
      if (len > 1)
	{
	  buf[len - 1] = '\0';
	  exit = strcmp(buf, "quit");
	  len = check_command(buf);
	  if (len == 1)
	    get_file(buf, ftp);
	  else if (len == 0)
	    do_simplecommand(ftp, buf);
	}
    }
  exit_client(ftp);
}
