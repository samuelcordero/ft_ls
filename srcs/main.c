#include "ft_ls.h"

void    freeAndExit(int exit_code) {
    exit(exit_code);
}

int main(int argc, char **argv) {
    ft_printf("args: %d, exec name:%s\n", argc, argv[0]);
    listDir(argv[1], 0);
/*     ft_printf("showing hidden files:\n");
    listDir(argv[1], __SHOWHIDDEN); */
    freeAndExit(0);
}