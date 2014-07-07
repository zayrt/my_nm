/*
** get_type.c for get_type in /home/zellou_i/rendu/PSU_2013_nmobjdump
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Mar 15 21:13:47 2014 ilyas zelloufi
** Last update Sun Mar 16 10:53:55 2014 ilyas zelloufi
*/

#include "my_nm.h"

void            show_struct_tab(t_struct *tab)
{
  int           i = 0;

  while (tab[i].name)
    {
      if (tab[i].value)
	{
	  if (tab[i].name[0] != 0 && tab[i].type != 0)
	    printf("%016x %c %s\n", (int)tab[i].value, tab[i].type, tab[i].name);
	}
      else
	if (tab[i].name[0] != 0 && tab[i].type != 0)
	  printf("                 %c %s\n", tab[i].type, tab[i].name);
      ++i;
    }
}

t_elf           *my_check_file(char *filename)
{
  t_elf         *ep;

  if ((ep = init(filename)) == NULL)
    return (NULL);
  ep->filename = filename;
  ep->maddr = mmap(NULL, ep->mlen, PROT_READ, MAP_SHARED, ep->fd, 0);
  if (ep->maddr == (void *) -1)
    {
      fprintf(stderr, "Can't mmap \"%s\": %s\n", filename, strerror(errno));
      return (NULL);
    }
  close(ep->fd);
  ep->ehdr = ep->maddr;
  if (strncmp((const char *)ep->ehdr->e_ident, ELFMAG, SELFMAG))
    {
      fprintf(stderr, "my_nm: %s: File format not recognized\n", filename);
      return (NULL);
    }
  if (ep->ehdr->e_ident[EI_CLASS] != ELFCLASS64)
    {
      fprintf(stderr, "my_nm: %s: File format is not 64 bits\n", filename);
      return (NULL);
    }
  return (ep);
}

void		second_get_type(Elf64_Sym sym, Elf64_Shdr *shdr, char *c)
{
  if (sym.st_shndx == SHN_ABS)
    *c = 'A';
  else if (sym.st_shndx == SHN_COMMON)
    *c = 'C';
  else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS &&
      shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    *c = 'B';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
	   && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
    *c = 'R';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
	   && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    *c = 'D';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
  	   && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    *c = 'T';
  else if (sym.st_shndx == SHT_DYNAMIC)
    *c = 'D';
  else
    *c = '?';
}

void		first_get_type(Elf64_Sym sym, Elf64_Shdr *shdr, char *c)
{
  if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
    *c = 'u';
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    {
      *c = 'W';
      if (sym.st_shndx == SHN_UNDEF)
	*c = 'w';
    }
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
    {
      *c = 'V';
      if (sym.st_shndx == SHN_UNDEF)
	*c = 'v';
    }
  else if (sym.st_shndx == SHN_UNDEF)
    *c = 'U';
  else if (sym.st_shndx == SHN_ABS)
    *c = 'A';
  else if (sym.st_shndx == SHN_COMMON)
    *c = 'C';
  else
    second_get_type(sym, shdr, c);
}

char            get_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
  char		c;

  first_get_type(sym, shdr, &c);
  if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
    c += 32;
  return (c);
}
