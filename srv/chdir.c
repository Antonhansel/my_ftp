/*
** chdir.c for chdir in /home/apollo/rendu/oldftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Fri Apr 11 22:18:48 2014 ribeaud antonin
** Last update Fri Apr 11 22:21:06 2014 ribeaud antonin
*/

#include "ftp.h"

void	my_chdir(t_ftp *ftp, char *buf)
{
  int	test;
  char  *newpath;

  newpath = NULL;
  if ((newpath = realpath(buf, newpath)) != NULL)
    {
      if ((test = strncmp(ftp->homepwd, newpath, strlen(ftp->homepwd))) == 0)
	test_chdir(ftp, buf, newpath);
      else
	{
	  send_message("Impossible to change directory\n", ftp);
	  printf("ERROR: impossible to change working directory to %s", buf);
	}

    }
  else
    {
      printf("ERROR: Cant resolve pathname %s\n", buf);
      send_message("Impossible to change directory\n", ftp);
    }
}

void	test_chdir(t_ftp *ftp, char *buf, char *newpath)
{
  int	ret;

  ret = chdir(buf);
  if (ret == -1)
    {
      send_message("Impossible to change directory\n", ftp);
      printf("ERROR: impossible to change working directory to %s", buf);
    }
  else
    {
      send_message("ok\n", ftp);
      printf("SUCCESS: working directory of %s was successfuly changed to %s\n"
	     , ftp->ipclient, newpath);
    }
}
