#include "ft_ls.h"

void    get_files_init(DIR **dir_ptr, struct dirent **directory, const char *path) {
    *directory = NULL;

    *dir_ptr = opendir(path);
    if (dir_ptr)
        *directory = readdir(*dir_ptr);
}

char    *isSubDir(char *subdir_name, char *curr_dir) {
    char        *subdir_path;
    if (curr_dir[ft_strlen(curr_dir) - 1] == '/') 
        subdir_path = ft_strjoin(curr_dir, subdir_name);
    else {
        char    *tmp = ft_strjoin(curr_dir, "/");
        subdir_path = ft_strjoin(tmp, subdir_name);
        free(tmp);
    }

    struct stat file_stat;
    if (stat(subdir_path, &file_stat) == -1) {
        perror("stat");
        free(subdir_path);
        return NULL;
    }

    if (S_ISDIR(file_stat.st_mode))
        return subdir_path;
    free(subdir_path);
    return NULL;
}

void    printFileDetails(char *file_name, char *dir_path) {
    char        *file_path;
    if (dir_path[ft_strlen(dir_path) - 1] == '/') 
        file_path = ft_strjoin(dir_path, file_name);
    else {
        char    *tmp = ft_strjoin(dir_path, "/");
        file_path = ft_strjoin(tmp, file_name);
        free(tmp);
    }
    struct stat file_stat;
    if (stat(file_path, &file_stat) == -1) {
        perror("stat");
        return ;
    }
    // File type
    ft_printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    // Owner permissions
    ft_printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
    // Group permissions
    ft_printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
    // Other permissions
    ft_printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");

    ft_printf(" ");

    // Print number of hard links
    ft_printf("%u ", file_stat.st_nlink);

    // Print owner and group name
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);
    if (pwd != NULL && grp != NULL) {
        ft_printf("%s %s ", pwd->pw_name, grp->gr_name);
    } else {
        ft_printf("%d %d ", file_stat.st_uid, file_stat.st_gid);
    }

    // Print file size
    ft_printf("%u ", file_stat.st_size);

    // Print last modification time using ctime()
    char *mod_time = ctime(&file_stat.st_mtime);
    // ctime() adds a newline at the end, so we remove it.
    mod_time[ft_strlen(mod_time) - 1] = '\0';
    ft_printf("%s ", mod_time);

    // Print file name
    ft_printf("%s\n", file_name);
    free(file_path);
}

void    printTotalBlocks(char **file_list, char *dir_path) {
    char        *file_path;
    struct stat file_stat;
    long        blocks = 0;
    long        block_size = sysconf(_SC_PAGESIZE) / 512;

    for (int i = 0; file_list[i]; ++i) {
        if (dir_path[ft_strlen(dir_path) - 1] == '/') 
            file_path = ft_strjoin(dir_path, file_list[i]);
        else {
            char    *tmp = ft_strjoin(dir_path, "/");
            file_path = ft_strjoin(tmp, file_list[i]);
            free(tmp);
        }
        if (stat(file_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }
        blocks += (file_stat.st_size) / block_size;
        free(file_path);
    }
    ft_printf("Total %u\n", blocks);
}

void    listDir(char *path, int flags) {
    DIR             *dir_ptr;
    struct dirent   *directory;
    char            *file_list[4096];
    char            *subdirs_list[4096];
    size_t          ctr = 0;

    get_files_init(&dir_ptr, &directory, path);
    if (!directory) {
        ft_putstr_fd("ft_ls: cannot access '", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putendl_fd("': No such file or directory", STDERR_FILENO);
        return ;
    }
    ft_bzero(file_list, sizeof(file_list));
    ft_bzero(subdirs_list, sizeof(subdirs_list));
    int i = 0;
    while (directory && i < 4096)
    {
        if (ft_strncmp(directory->d_name, ".", 1) || flags & __SHOWHIDDEN) { //dont check hidden files unless flag -a active
            file_list[i++] = ft_strdup(directory->d_name);
            //ft_printf("%s: %d %d\n", directory->d_name, directory->d_reclen, directory->d_type);
        }
        directory = readdir(dir_ptr);
    }
    closedir(dir_ptr);
    sortFiles(file_list, flags & __SORTTIME, flags & __REVERSESORT, path); //sort files (by name by default)
    if (flags & __PRINT_DIRNAME) {
        ft_printf("%s:\n", path);
    }
    if (flags & __SHOWLIST) {
        printTotalBlocks(file_list, path);
        for (i = 0; file_list[i]; ++i) {
            char    *subdir = NULL;
            printFileDetails(file_list[i], path);
            if (flags & __RECURSIVE && NULL != (subdir = isSubDir(file_list[i], path))) {
                subdirs_list[ctr++] = subdir;
            }
        }
    } else {
        for (i = 0; file_list[i]; ++i) {
            ft_printf("%s\n", file_list[i]);
        }
    }
    if (flags & __PRINT_DIRNAME) {
        ft_printf("\n");
    }
    if (flags & __RECURSIVE) {
        for (i = 0; subdirs_list[i]; ++i) {
            listDir(subdirs_list[i], flags);
        }
    }
}
