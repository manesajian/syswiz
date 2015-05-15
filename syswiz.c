#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LEN    2048
#define MAX_BUF_LEN     8192

struct options {
    int find_files_from_inode;
    int inode;
    int path_set;
    char path[MAX_PATH_LEN];
    int verbose;
};

struct output {
    char buffer[MAX_BUF_LEN];
    int buf_len;
};

// Fills options structure. Returns zero on error
int parse_options(struct options *opt, int argc, char **argv);

void handle_output(struct options *opt, struct output *out);

// Verifies existence of path. Adjusts path buffer from relative location
//  to absolute path if needed. Returns zero on error.
int verify_path(struct options * opt, char *path);

struct output *find_files(struct options *opt, char *path);

int main(int argc, char **argv)
{
    // Place command-line arguments into options structure
    struct options opt;
    if (parse_options(&opt, argc, argv)) {
        return 1;
    } 

    // Prints files matching inode number and descending from path
    if (opt.find_files_from_inode)
        handle_output(&opt, find_files(&opt, opt.path));

    return 0;
}

const char usage[] = "Usage: syswiz [-h] [-i inode] [-p path] [-v]";

int parse_options(struct options *opt, int argc, char **argv)
{
    // Initialize options
    memset(opt, 0, sizeof(struct options));

    char c;
    while ((c = getopt (argc, argv, "hi:p:v")) != -1) {
        switch (c) {
            case 'i':
                opt->find_files_from_inode = 1;
                opt->inode = atoi(optarg);
                break;
            case 'h':
                printf("%s\n", usage);
                break;
            case 'p':
                opt->path_set = 1;
                strncpy(opt->path, optarg, strlen(optarg));
                break;
            case 'v':
                opt->verbose = 1;
                break;
           default:
                fprintf(stderr, "Unrecognized arg: %c\n", c);
                return 1;
       }
    }

    if (opt->path_set) {
        if (opt->verbose)
            printf("Verifying path %s ...\n", opt->path);

        if (!verify_path(opt, opt->path)) {
            printf("Invalid path: %s\n", opt->path);
            return 1;
        }

        if (opt->verbose)
            printf("Path is valid.\n");
    }

    return 0;
}

void handle_output(struct options *opt, struct output *out)
{
    printf("handle_output()\n");

    printf("OUTPUT: %s\n", out->buffer);

    free(out);
}

int verify_path(struct options * opt, char *path)
{
    DIR *dir = opendir(path);
    if (opendir(path)) {
        // path exists
        closedir(dir);
        return 1;
    }
    else if (errno == ENOENT) {
        // try current working directory
        char *cwd = getcwd(NULL, 0);

        char pathbuf[MAX_PATH_LEN];
        snprintf(pathbuf, MAX_PATH_LEN, "%s/%s", cwd, path);

        if (opendir(pathbuf)) {
            if (opt->verbose)
                printf("Converted path from %s to %s.\n", path, pathbuf);

            // path exists
            closedir(dir);
            return 1;
        }

        printf("Directory %s does not exist.\n", path);
    }
    else {
        printf("Directory %s could not be accessed.\n", path);
    }

    return 0;
}

struct output *find_files(struct options *opt, char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    struct output *out;

    if ((dp = opendir(path)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", path);
        return;
    }

    if (opt->verbose)
        printf("Doing chdir(%s) ...\n", path);

    chdir(path);

    // Allocate and initialize output structure
    out = malloc(sizeof(struct output));
    memset(out, 0, sizeof(struct output));

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            // Ignore . and ..
            if (strcmp(".", entry->d_name) == 0 ||
                strcmp("..", entry->d_name) == 0)
                continue;

            // check for inode match
            if (statbuf.st_ino == opt->inode) {
                int bytes = snprintf(out->buffer,
                                     MAX_BUF_LEN - out->buf_len,
                                     "%s\n",
                                     entry->d_name);
                out->buf_len += bytes;
            } 

            // Recurse
            find_files(opt, entry->d_name);
        }
        else {
            // check for inode match
            if (statbuf.st_ino == opt->inode) {
                int bytes = snprintf(out->buffer,
                                     MAX_BUF_LEN - out->buf_len,
                                     "%s\n",
                                     entry->d_name);
                out->buf_len += bytes;
            } 
        }
    }

    chdir("..");
    closedir(dp);

    return out;
}

