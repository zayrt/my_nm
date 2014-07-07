/*
** elf.c for elf in /home/zellou_i/rendu/PSU_2013_nmobjdump
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Wed Mar 12 15:06:46 2014 ilyas zelloufi
** Last update Sun Mar 16 10:52:26 2014 ilyas zelloufi
*/

#include "my_nm.h"

int		compare_name(void const *a, void const *b)
{
  t_struct const *ptr_a;
  t_struct const *ptr_b;

  ptr_a = a;
  ptr_b = b;
  if (ptr_a->name == NULL || ptr_b->name == NULL)
    return (0);
  return (strcmp(ptr_a->name, ptr_b->name));
}

t_struct	*my_fill_struct(t_struct *data, t_elf *ep, char *tmp)
{
  int		i;

  i = 0;
  while (ep->symtab != ep->symtab_end && ep->symtab)
    {
      if (tmp != &ep->strtab[ep->symtab->st_name] &&
	  get_type(*(ep->symtab), ep->shdr) != 'a')
	{
	  data[i].name = &ep->strtab[ep->symtab->st_name];
	  if (data[i].name[0] == '\0' || data[i].name[0] == '\n')
	    {
	      fprintf(stderr, "my_nm: %s: no symbols\n", ep->filename);
	      return (NULL);
	    }
	  data[i].type = get_type(*(ep->symtab), ep->shdr);
	  if (ep->symtab->st_value != 0)
	    data[i].value = ep->symtab->st_value;
	  ++i;
	}
      ++ep->symtab;
    }
  return (data);
}

t_struct	*my_init_nm(t_elf *ep, int i)
{
  char		*tmp;
  int		nb_sym;
  t_struct	*data;

  ep->symtab = (Elf64_Sym *)(ep->maddr + ep->shdr[i].sh_offset);
  ep->symtab_end = (Elf64_Sym *)((char *)ep->symtab + ep->shdr[i].sh_size);
  ep->strtab = (char *)(ep->maddr + ep->shdr[ep->shdr[i].sh_link].sh_offset);
  tmp = &ep->strtab[ep->symtab->st_name];
  nb_sym = (int)(ep->symtab_end - ep->symtab + 1);
  if ((data = malloc(sizeof(t_struct) * nb_sym)) == NULL)
    exit (EXIT_FAILURE);
  if ((data = my_fill_struct(data, ep, tmp)) == NULL)
    return (NULL);
  return (data);
}

int		my_nm(char *filename)
{
  t_elf		*ep;
  int		i;
  t_struct	*data;

  i = 0;
  if ((ep = my_check_file(filename)) == NULL)
    return (-1);
  ep->shdr = (Elf64_Shdr *)(ep->maddr + ep->ehdr->e_shoff);
  while (i < ep->ehdr->e_shnum)
    {
      if (ep->shdr[i].sh_type == SHT_SYMTAB)
	{
	  if ((data = my_init_nm(ep, i)) == NULL)
	    return (-1);
	  qsort(data, i, sizeof(t_struct), compare_name);
	  show_struct_tab(data);
	  munmap(ep->maddr, ep->mlen);
	  return (0);
	}
      i++;
    }
  fprintf(stderr, "my_nm: %s: no symbols\n", filename);
  return (-1);
}

