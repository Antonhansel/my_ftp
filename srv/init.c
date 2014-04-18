/*
** init.c for init in /home/apollo/rendu/my_ftp
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr  2 23:38:30 2014 ribeaud antonin
** Last update Sun Apr 13 15:24:23 2014 ribeaud antonin
*/

#include "ftp.h"

int		get_infos(t_ftp *ftp)
{
  size_t	toto;
  FILE		*pFile;
  char		*buffer;

  pFile = fopen(".users.ftp", "r");
  buffer = NULL;
  toto = 4096;
  if (getline(&buffer, &toto, pFile) != -1)
    {
      buffer[strlen(buffer) - 1] = '\0';
      ftp->username = strdup(buffer);
    }
  else
    return (0);
  if (getline(&buffer, &toto, pFile) != -1)
    {
      buffer[strlen(buffer) - 1] = '\0';
      ftp->password = strdup(buffer);
      return (1);
    }
  else
    return (0);
}

int	xbind(t_ftp *ftp)
{
  int	error;

  error = bind(ftp->s, (const struct sockaddr*)&ftp->sin, sizeof(ftp->sin));
  if (error == -1)
    {
      close(ftp->s);
      my_error("Error on binding");
      return (-1);
    }
}

int	init_protocol(int port, t_ftp *ftp)
{
  int	error;

  ftp->pe = getprotobyname("TCP");
  ftp->s = socket(AF_INET, SOCK_STREAM, ftp->pe->p_proto);
  if (ftp->s == -1)
    {
      my_error("Couldn't initialize sockets");
      return (0);
    }
  ftp->sin.sin_family = AF_INET;
  ftp->sin.sin_port = htons(port);
  ftp->sin.sin_addr.s_addr = INADDR_ANY;
  error = xbind(ftp);
  if (error == -1)
    return (0);
  error = listen(ftp->s, 4);
  if (error == -1)
    {
      close(ftp->s);
      my_error("Error on connecting");
      return (0);
    }
  return (1);
}

int	get_home(t_ftp *ftp)
{
  char	cwd[4096];

  memset(cwd, 0, 4096);
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
      ftp->homepwd = strdup(cwd);
      return (1);
    }
  else
    return (0);
}

void	init_server(int port, t_ftp *ftp)
{
  if (init_protocol(port, ftp) && get_home(ftp) && get_infos(ftp))
    loop_server(ftp);
  else
    {
      printf("Initialization failed. Stopping server...\n");
      close(ftp->s);
    }
}
