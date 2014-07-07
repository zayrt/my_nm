/*
** main.c for main in /home/zellou_i/rendu/PSU_2013_nmobjdump
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Mar 15 17:58:23 2014 ilyas zelloufi
** Last update Sun Mar 16 11:35:00 2014 ilyas zelloufi
*/

#include "my_nm.h"

t_elf           *init(char *filename)
{
  struct        stat sbuf;
  t_elf         *ep;

  if ((ep = (t_elf *) malloc(sizeof(t_elf))) == NULL)
    {
      fprintf (stderr, "Malloc failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  if ((ep->fd = open(filename, O_RDONLY)) == -1)
    {
      fprintf (stderr, "my_nm: '%s': %s\n", filename, strerror(errno));
      return (NULL);
    }
  if (fstat(ep->fd, &sbuf) == -1)
    {
      fprintf (stderr, "Can't stat \"%s\": %s\n", filename, strerror(errno));
      return (NULL);
    }
  if (sbuf.st_size < (unsigned)sizeof(Elf64_Ehdr))
    {
      fprintf (stderr, "my_nm: %s: File format not recognized\n", filename);
      return (NULL);
    }
  ep->mlen = sbuf.st_size;
  return (ep);
}

int             main(int ac, char **av)
{
  int		i;

  i = 1;
  if (ac == 1)
    my_nm("a.out");
  else if (ac == 2)
    my_nm(av[1]);
  else
    {
      while (av[i])
	{
	  printf("%s:\n", av[i]);
	  my_nm(av[i]);
	  ++i;
	}
    }
  return (0);
}
