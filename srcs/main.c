#include "ft_ls.h"

void    freeAndExit(int exit_code) {
    exit(exit_code);
}

int main(int argc, char **argv) {
    char    *path_list[4096];
    ft_bzero(path_list, sizeof(path_list));

    int flags = parseArgs(argc, argv, path_list);

    //sort path_list (ascii by default, time if -t flag)
    sortFiles(path_list, flags & __SORTTIME, flags & __REVERSESORT, "");
    //duplicates are ignored and listed twice, but there is a preprocesing for unaccessible/not dirs
    for (int i = 0; path_list[i]; ++i) {
        listDir(path_list[i], flags);
    }
    freeList(path_list);
    freeAndExit(0);
}