#include "ft_ls.h"

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
    if (!path_list[0])
        path_list[0] = ft_strdup(".");
    if (path_list[1] || flags & __RECURSIVE)
        flags |= __PRINT_DIRNAME;
    return flags;
}
