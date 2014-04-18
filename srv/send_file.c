/*
** send_file.c for send_file in /home/apollo/rendu/newftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Tue Apr  8 18:43:41 2014 ribeaud antonin
** Last update Sun Apr 13 15:25:14 2014 ribeaud antonin
*/

#include "ftp.h"

int	bad_file(char *arg)
{
  printf("%s: No such file or directory\n", arg);
  return (-1);
}

int		open_fd(t_ftp *ftp, char *arg)
{
  char		*newpath;
  int		fd;
  struct stat	buf;

  newpath = NULL;
  fd = -1;
  if ((newpath = realpath(arg, NULL)) != NULL)
    {
      if (stat(arg, &buf) == -1)
	return (bad_file(arg));
      ftp->filesize = buf.st_size;
      if (buf.st_size == 0 || (buf.st_mode & S_IFDIR))
	return (-1);
    }
  else
    return (-1);
  if (strncmp(ftp->homepwd, newpath, strlen(ftp->homepwd)) != 0)
    return (-1);
  if ((fd = open(arg, O_RDONLY)) == -1)
    {
      printf("No such file or directory\n");
      return (-1);
    }
  return (fd);
}

void	send_file(t_ftp *ftp, int fd)
{
  char	buffer[4096];
  int	ret;
  int	size;

  size = 0;
  memset(buffer, 0, 4096);
  read(ftp->cs, buffer, sizeof(buffer));
  if (strcmp(buffer, "...") == 0)
    {
      send_size(ftp);
      memset(buffer, 0, 4096);
      while (size < ftp->filesize &&
	     (ret = read(fd, buffer, sizeof(buffer))) > 0)
	{
	  size += 4096;
	  send_message(buffer, ftp);
	  memset(buffer, 0, 4096);
	}
    }
  else
    transfer_failed(ftp, fd);
}

void	get_file(t_ftp *ftp, char **args)
{
  int	fd;

  if (args[1] == NULL)
    {
      send_message("Get command needs an argument\n", ftp);
      printf("Get command needs an argument\n");
    }
  else if ((fd = open_fd(ftp, args[1])) != -1)
    {
      send_message("...", ftp);
      printf("Transfer starting...\n");
      send_file(ftp, fd);
    }
  else
    {
      send_message("Fail\n", ftp);
      printf("Transfer failed\n");
    }
}
