#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

#define MAX_PATH_LEN    2048

struct options {
    int find_files_from_inode;
    int inode;
    int path_set;
    char path[MAX_PATH_LEN];
    int verbose;
};

struct output {

};

// Fills options structure, returns non-zero on error
int parse_options(struct options *opt, int argc, char **argv);

void handle_output(struct options *opt, struct output *out);

int verify_path(char *path);

struct output *find_files(struct options *opt, char *path);

int main(int argc, char **argv)
{
    struct options opt;
    struct output out;
    if (parse_options(&opt, argc, argv)) {
        return 1;
    } 

    if (opt.find_files_from_inode)
        handle_output(&opt, find_files(&opt, opt.path));

    return 0;
}

const char usage[] = "Usage: syswiz [-i inode] [-p path] [-v]";

int parse_options(struct options *opt, int argc, char **argv)
{
    // Initialize options
    memset(opt, 0, sizeof(struct options));

    char c;
    while ((c = getopt (argc, argv, "i:p:v")) != -1) {
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
                printf("Unrecognized arg: %c\n", c);
                return 1;
       }
    }

    if (opt->path_set) {
        printf("Verifying path ...");
        if (!verify_path(opt->path))
            printf("Invalid path: %s\n", opt->path);
            return 1;
    }

    return 0;
}

void handle_output(struct options *opt, struct output *out)
{
    printf("handle_output()\n");
}

int verify_path(char *path)
{
    DIR *dir = opendir(path);
    if (opendir(path)) {
        // path exists
        closedir(dir);
    }
    else if (errno == ENOENT) {
        printf("Directory %s does not exist.", path);
    }
    else {
        printf("Directory %s could not be accessed.", path);
    }
}

struct output *find_files(struct options *opt, char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(path)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", path);
        return;
    }

    chdir(path);

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            // Ignore . and ..
            if(strcmp(".", entry->d_name) == 0 ||
               strcmp("..", entry->d_name) == 0)
                continue;

            // Recurse
            find_files(opt, entry->d_name);
        }
        else {
            // Handle file
            //entry->d_name ...
        }
    }

    chdir("..");
    closedir(dp);
}

