/*
** password.c for password in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:30:06 2014 ribeaud antonin
** Last update Sun Apr 13 15:25:14 2014 ribeaud antonin
*/

#include "ftp.h"

int	send_ok(t_ftp *ftp)
{
  send_message("USER ok. Enter your password\n", ftp);
  printf("User ok, waiting for password\n");
  return (1);
}

int	read_user(t_ftp *ftp)
{
  int	len;
  char	buf[512];

  memset(buf, 0, 512);
  len = read(ftp->cs, buf, 512);
  if (len > 0)
    {
      buf[len] = '\0';
      if (strcmp(buf, ftp->username) == 0)
	return (send_ok(ftp));
      else
	{
	  send_message("Wrong user. Goodbye...\n", ftp);
	  printf("Wrong user, kicking client...\n");
	  return (0);
	}
    }
  return (0);
}

int	ok_password(t_ftp *ftp)
{
  send_message("You are now logged in...\n", ftp);
  printf(PASSOK, ftp->ipclient);
  return (1);
}

int	read_password(t_ftp *ftp)
{
  int	len;
  char	buf[512];

  memset(buf, 0, 512);
  len = read(ftp->cs, buf, 512);
  if (len > 0)
    {
      buf[len] = '\0';
      if (strcmp(buf, ftp->password) == 0)
	return (ok_password(ftp));
      else
	{
	  send_message("Wrong password. Goodbye...\n", ftp);
	  printf("Wrong password, kicking client...\n");
	  return (0);
	}
    }
  return (0);
}
