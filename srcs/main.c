#include "ft_ls.h"

void    freeAndExit(int exit_code) {
    exit(exit_code);
}

int parseArgs(int argc, char **argv, char **path_list) {
    int flags = 0;
    int ctr = 0;
    int i;
    for (i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') { //parse arg
            int j;
            for (j = 1; argv[i][j]; ++j) {
                if (argv[i][j] == 'R')
                    flags |= __RECURSIVE;
                else if (argv[i][j] == 'a')
                    flags |= __SHOWHIDDEN;
                else if (argv[i][j] == 'l')
                    flags |= __SHOWLIST;
                else if (argv[i][j] == 't')
                    flags |= __SORTTIME;
                else if (argv[i][j] == 'r')
                    flags |= __REVERSESORT;
                else if (argv[i][j] == '-')
                    break ;
            }
            if (argv[i][j] == '-'){
                ++i;
                break ;
            }
        } else {
            path_list[ctr++] = ft_strdup(argv[i]);
        }
    }
    while (argv[i]) {
        path_list[ctr++] = ft_strdup(argv[i]);
        ++i;
    }
    return flags;
}

int main(int argc, char **argv) {
    ft_printf("args: %d, exec name:%s\n", argc, argv[0]);
    
    char    *path_list[4096];
    ft_bzero(path_list, sizeof(path_list));

    int flags = parseArgs(argc, argv, path_list);
    //here path_list should be sorted (ascii by default, time if -t flag)
    //duplicates are ignored and listed twice
    for (int i = 0; path_list[i]; ++i) {
        listDir(path_list[i], flags);
    }
    
    freeAndExit(0);
}