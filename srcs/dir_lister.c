#include "ft_ls.h"

void    get_files_init(DIR **dir_ptr, struct dirent **directory, const char *path)
{
    *dir_ptr = opendir(path);
    *directory = readdir(*dir_ptr);
}

void    listDir(const char *path, int flags)
{
    DIR                *dir_ptr;
    struct dirent    *directory;
    char            *file_list;
    char            *tmp;

    get_files_init(&dir_ptr, &directory, path);
    file_list = ft_strdup("");
    if (!directory)
        return ;
    while (directory)
    {
        if (ft_strncmp(directory->d_name, ".", 1) || flags & __SHOWHIDDEN) {
            tmp = ft_strjoin(file_list, directory->d_name);
            free(file_list);
            file_list = ft_strjoin(tmp, " ");
            free(tmp);
        }
        directory = readdir(dir_ptr);
    }
    tmp = ft_strtrim(file_list, " \n\t\r\v");
    free(file_list);
    closedir(dir_ptr);
    ft_printf("%s\n", tmp);
    free(tmp);
}
