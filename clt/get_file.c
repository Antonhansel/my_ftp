/*
** get_file.c for get_file in /home/apollo/rendu/newftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Tue Apr  8 17:37:07 2014 ribeaud antonin
** Last update Fri Apr 11 21:02:18 2014 ribeaud antonin
*/

#include "client.h"

int	get_size(t_ftp *ftp)
{
  char	buf[128];
  int	size;

  memset(buf, 0, sizeof(buf));
  if (read(ftp->s, buf, sizeof(buf)) > 0)
    {
      size = atoi(buf);
      printf("Total file size %i\n", size);
      return (size);
    }
  else
    return (0);
}

void	transfer_file(FILE *file, t_ftp *ftp)
{
  int	len;
  int	cont;
  int	size;
  char	buf[BUFF_SIZE];

  memset(buf, 0, sizeof(buf));
  cont = 0;
  if ((size = get_size(ftp)) != 0)
    {
      while (cont < size && (len = read(ftp->s, buf, sizeof(buf))) > 0)
	{
	  if (len < 4096)
	    cont = size;
	  cont += 4096;
	  fprintf(file, "%s", buf);
	  memset(buf, 0, sizeof(buf));
	}
      printf("Transfer complete!\n");
    }
}

void	fail_local(t_ftp *ftp, char *arg)
{
  write(ftp->s, "..", 2);
  printf("Unable to create local file %s\n", arg);
}

void	get_file(char *buf, t_ftp *ftp)
{
  int	len;
  FILE	*file;
  char	**command;

  command = my_str_to_wordtab(buf, ' ');
  write(ftp->s, buf, strlen(buf));
  memset(buf, 0, sizeof(buf));
  len = read(ftp->s, buf, sizeof(buf));
  if (len > 0 && strcmp(buf, "...") == 0)
    {
      file = open_file(getfilename(command[1]));
      if (file != NULL)
	{
	  printf("Transfer starting...\n");
	  write(ftp->s, buf, strlen(buf));
	  transfer_file(file, ftp);
	  fclose(file);
	}
      else
	fail_local(ftp, command[1]);
    }
  else
    printf("Transfer failed\n");
}
