#ifndef __FT_LS__
# define __FT_LS__
# include <sys/types.h>
# include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

# include "libft.h"


# define __RECURSIVE 1
# define __SHOWHIDDEN 2
# define __SHOWLIST 4
# define __SORTTIME 8
# define __REVERSESORT 16
# define __PRINT_DIRNAME 32

/*
    prints the contents of a dir pointed by path, with style/options encoded in flags as a bitmasks:
    active on high
        -1 encodes recursive (-R flag)
        -2 encodes show hidden (-a flag)
        -4 encodes show list (-l flag)
        -8 encodes sort by time (-t flag)
        -16 encodes reverse sort order (-r flag)
*/
void    listDir(char *path, int flags);
void    freeAndExit(int exit_code);

//parser.c

int parseArgs(int argc, char **argv, char **path_list);

//utils.c

int	    ft_strncasecmp(const char *s1, const char *s2, size_t n);
void    sortFiles(char **file_list, int sb_time, int reverse_sort, char *dir_path);
void    freeList(char **list);

#endif
