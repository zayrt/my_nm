/*
** elf.h for elf in /home/zellou_i/rendu/PSU_2013_nmobjdump
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Wed Mar 12 14:01:32 2014 ilyas zelloufi
** Last update Sun Mar 16 01:07:29 2014 ilyas zelloufi
*/

#ifndef ELF_H__
# define ELF_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <elf.h>

typedef struct s_elf {
  void		*maddr;
  int		mlen;
  Elf64_Ehdr	*ehdr;
  Elf64_Shdr	*shdr;
  Elf64_Sym	*symtab;
  Elf64_Sym	*symtab_end;
  char		*strtab;
  char		*filename;
  int		fd;
} t_elf;

typedef struct s_struct {
  char		*name;
  Elf64_Addr	value;
  char		type;
} t_struct;

t_elf           *init(char *filename);
int		compare_name(void const *a, void const *b);
void		show_struct_tab(t_struct *tab);
t_elf		*my_check_file(char *);
t_struct        *my_init_nm(t_elf *ep, int i);
t_struct	*my_fill_struct(t_struct *, t_elf *, char *);
int	        my_nm(char *filename);
char            get_type(Elf64_Sym sym, Elf64_Shdr *shdr);

#endif /* ELF_H__ */
