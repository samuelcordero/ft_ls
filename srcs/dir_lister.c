#include "ft_ls.h"

static int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    i = 0;
    if (n == 0)
        return (0);

    while (i < n && s1[i] != '\0' && s2[i] != '\0') {
        unsigned char c1 = (unsigned char)ft_tolower(s1[i]);
        unsigned char c2 = (unsigned char)ft_tolower(s2[i]);

        if (c1 != c2)
            return c1 - c2;
        i++;
    }

    if (i < n) {
        unsigned char c1 = (unsigned char)ft_tolower(s1[i]);
        unsigned char c2 = (unsigned char)ft_tolower(s2[i]);
        return c1 - c2;
    }

    return 0;
}

void    get_files_init(DIR **dir_ptr, struct dirent **directory, const char *path)
{
    *dir_ptr = opendir(path);
    *directory = readdir(*dir_ptr);
}

static void sortFiles(char **file_list, int sb_time, int reverse_sort) {
    int swapped;
    if (sb_time) {
        ft_printf("Work in progress, no t flag yet\n");
    }    
    // char * ascii bubble sort
    do {
        swapped = 0;
        for (int i = 0; file_list[i + 1]; i++) {
            if ((reverse_sort == 0 && ft_strncasecmp(file_list[i], file_list[i + 1], ft_strlen(file_list[i])) > 0) ||
                (reverse_sort == 1 && ft_strncasecmp(file_list[i], file_list[i + 1], ft_strlen(file_list[i])) < 0)) { // Ascending order if reverse_sort == 0, descending if reverse_sort == 1
                char *tmp = file_list[i];
                file_list[i] = file_list[i + 1];
                file_list[i + 1] = tmp;
                swapped = 1;
            }
        }
    } while (swapped);
}

void    listDir(const char *path, int flags)
{
    DIR             *dir_ptr;
    struct dirent   *directory;
    char            *file_list[4096];

    get_files_init(&dir_ptr, &directory, path);
    if (!directory)
        return ;
    ft_bzero(file_list, sizeof(file_list));
    int i = 0;
    while (directory && i < 4096)
    {
        if (ft_strncmp(directory->d_name, ".", 1) || flags & __SHOWHIDDEN) { //dont check hidden files unless flag -a active
            file_list[i++] = ft_strdup(directory->d_name);
            //ft_printf("%s: %d %d\n", directory->d_name, directory->d_reclen, directory->d_type);
        }
        directory = readdir(dir_ptr);
    }
    sortFiles(file_list, flags & __SORTTIME, flags & __REVERSESORT); //sort files (by name by default)
    for (i = 0; file_list[i]; ++i) {
        ft_printf("%s\n", file_list[i]);
    }
    closedir(dir_ptr);
}
