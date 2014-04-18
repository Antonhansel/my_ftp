/*
** password.c for password in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:34:25 2014 ribeaud antonin
** Last update Wed Apr  9 14:44:55 2014 ribeaud antonin
*/

#include "client.h"

int	send_username(t_ftp *ftp)
{
  int	len;
  char	buf[512];
  char	*password;

  memset(buf, 0, 512);
  read(ftp->s, buf, 512);
  write(1, buf, strlen(buf));
  memset(buf, 0, 512);
  write(1, "USER: ", 6);
  len = read(0, buf, 512);
  buf[len - 1] = '\0';
  password = crypt(buf, "zA");
  write(ftp->s, password, strlen(buf));
  memset(buf, 0, 512);
  read(ftp->s, buf, 512);
  write(1, buf, strlen(buf));
  if (strcmp(buf, "USER ok. Enter your password\n") == 0)
    return (1);
  return (0);
}

int	send_password(t_ftp *ftp)
{
  int	len;
  char	buf[512];
  char	*password;

  memset(buf, 0, 512);
  write(1, "PASS: ", 6);
  len = read(0, buf, 512);
  buf[len - 1] = '\0';
  password = crypt(buf, "zA");
  write(ftp->s, password, strlen(buf));
  memset(buf, 0, 512);
  read(ftp->s, buf, 512);
  write(1, buf, strlen(buf));
  if (strcmp(buf, "You are now logged in...\n") == 0)
    return (1);
  return (0);
}
