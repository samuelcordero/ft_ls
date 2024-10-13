#include "ft_ls.h"

static int compare_files(const char *file1, const char *file2, int reverse_sort, char *dir_path) {
    struct stat stat1, stat2;
    char        *file_path1, *file_path2;

    if (dir_path[ft_strlen(dir_path) - 1] == '/' || !dir_path[0]) {
        file_path1 = ft_strjoin(dir_path, file1);
        file_path2 = ft_strjoin(dir_path, file2);
    }
    else {
        char    *tmp = ft_strjoin(dir_path, "/");
        file_path1 = ft_strjoin(tmp, file1);
        file_path2 = ft_strjoin(tmp, file2);
        free(tmp);
    }
    
    if (stat(file_path1, &stat1) != 0 || stat(file_path2, &stat2) != 0) {
        perror("stat");
        //ft_printf("s1:%s s2:%s\n", file_path1, file_path2);
        return 0; // If stat fails, consider them equal for sorting
    }
    //ft_printf("s1:%s at %u; s2:%s at %u\n", file_path1, stat1.st_mtime, file_path2, stat2.st_mtime);
    free(file_path1);
    free(file_path2);

    if (stat1.st_mtime == stat2.st_mtime) {
        if (reverse_sort) {
            return ft_strncasecmp(file1, file2, ft_strlen(file1)) < 0; // Descending order
        } else {
            return ft_strncasecmp(file1, file2, ft_strlen(file1)) > 0; // Descending order
        }
    }
    if (reverse_sort) {
        return stat1.st_mtime > stat2.st_mtime; // Descending order
    } else {
        return stat1.st_mtime < stat2.st_mtime; // Ascending order
    }
}

int	ft_strncasecmp(const char *s1, const char *s2, size_t n) {
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

void sortFiles(char **file_list, int sb_time, int reverse_sort, char *dir_path) {
    int swapped;
    if (sb_time) {
        do {
            swapped = 0;
            for (int i = 0; file_list[i + 1]; i++) {
                if (compare_files(file_list[i], file_list[i + 1], reverse_sort, dir_path)) { // Ascending order if reverse_sort == 0, descending if reverse_sort == 1
                    char *tmp = file_list[i];
                    file_list[i] = file_list[i + 1];
                    file_list[i + 1] = tmp;
                    swapped = 1;
                }
            }
        } while (swapped);
    } else {
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
}

void    freeList(char **list) {
    for (int i = 0; list[i]; ++i) {
        free(list[i]);
    }
}
