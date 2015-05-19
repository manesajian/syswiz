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
    int verbose;
    int file_set;
    int path_set;
    int inode;
    char file[MAX_PATH_LEN];
    char path[MAX_PATH_LEN];
};

struct output {
    char buffer[MAX_BUF_LEN];
    int buf_len;
};

// Fills options structure. Returns zero on error
int parse_options(struct options *opt, int argc, char **argv);

// Outputs and frees output struct
void handle_output(struct options *opt, struct output *out);

// Verifies existence of path. Adjusts path buffer from relative location
//  to absolute path if needed. Returns zero on error.
int verify_path(struct options * opt, char *path);

// Prepares stat struct for output
struct output *format_stat(struct options *opt, struct stat *st);

struct output *find_files(struct options *opt, char *path);

int main(int argc, char **argv)
{
    // Place command-line arguments into options structure
    struct options opt;
    if (parse_options(&opt, argc, argv)) {
        return 1;
    } 

    if (opt.file_set) {
        struct stat st;
        if (stat(opt.file, &st) == -1) {
            fprintf(stderr, "could not stat file: %s\n", opt.file);
            return 1;
        }

        // Remember file inode
        opt.inode = st.st_ino;

        struct output *out;
        if (opt.path_set) {
            out = find_files(&opt, opt.path);
        } else {
            // Default to cwd for search path
            char *cwd = getcwd(NULL, 0);
            out = find_files(&opt, cwd);
            free(cwd);
        }

        // Output all known hard-linked versions of file
        handle_output(&opt, out);

        // Output stat(file)
        handle_output(&opt, format_stat(&opt, &st));

// TODO: don't forget to detect when there are hard-linked version that are
//  unknown in location
    }

    return 0;
}

const char usage[] = "Usage: syswiz [-f *] [-h] [-p] [-v]";

int parse_options(struct options *opt, int argc, char **argv)
{
    // Initialize options
    memset(opt, 0, sizeof(struct options));

    if (argc == 1) {
        printf("%s\n", usage);
        return 1;
    }

    char c;
    while ((c = getopt (argc, argv, "f:hp:v")) != -1) {
        switch (c) {
            case 'f':
                opt->file_set = 1;
                strncpy(opt->file, optarg, strlen(optarg));
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

    if (opt->file_set) {
        if (!verify_path(opt, opt->file)) {
            printf("Invalid file: %s\n", opt->file);
            return 1;
        }
    }

    if (opt->path_set) {
        if (!verify_path(opt, opt->path)) {
            printf("Invalid path: %s\n", opt->path);
            return 1;
        }
    }

    return 0;
}

void handle_output(struct options *opt, struct output *out)
{
    if (out == NULL)
        return;

    printf("%s", out->buffer);

    free(out);
}

int verify_path(struct options * opt, char *path)
{
    DIR *dir = opendir(path);
    if (opendir(path)) {
        // path exists
        closedir(dir);
        return 1;
    } else if (errno == ENOENT) {
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
    } else {
        printf("Directory %s could not be accessed.\n", path);
    }

    return 0;
}

/*
 * Prepares stat struct for output
 */
struct output *format_stat(struct options *opt, struct stat *st)
{
    struct output *out;

    // Allocate and initialize output structure
    out = malloc(sizeof(struct output));
    memset(out, 0, sizeof(struct output));

    int bytes = snprintf(out->buffer,
                         MAX_BUF_LEN,
                         "  on device: %i\n"
                         "      inode: %i\n"
                         " protection: %i\n"
                         " hard links: %i\n"
                         "       user: %i\n"
                         "      group: %i\n"
                         "  is device: %i\n"
                         " total size: %i\n"
                         " block size: %i\n"
                         "     blocks: %i\n"
                         "last access: %i\n"
                         "last modify: %i\n"
                         "last change: %i\n",
                         (int)st->st_dev,
                         (int)st->st_ino,
                         (int)st->st_mode,
                         (int)st->st_nlink,
                         (int)st->st_uid,
                         (int)st->st_gid,
                         (int)st->st_rdev,
                         (int)st->st_size,
                         (int)st->st_blksize,
                         (int)st->st_blocks,
                         (int)st->st_atime,
                         (int)st->st_mtime,
                         (int)st->st_ctime);

    out->buf_len += bytes;
}

/*
 * Recurses to search path for all files matching opt->inode
 */
struct output *find_files(struct options *opt, char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    struct output *out;

    if ((dp = opendir(path)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", path);
        return NULL;
    }

    // Fill in inode if needed
    if (!opt->inode) {
        if (opt->verbose)
            printf("Doing stat(%s) ...\n", opt->file);

        if (stat(opt->file, &st) == -1) {
            fprintf(stderr, "could not stat file: %s\n", opt->file);
            return NULL;
        }

        opt->inode = st.st_ino;
    }

    if (opt->verbose)
        printf("Doing chdir(%s) ...\n", path);

    chdir(path);

    // Allocate and initialize output structure
    out = malloc(sizeof(struct output));
    memset(out, 0, sizeof(struct output));

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &st);
        if (S_ISDIR(st.st_mode)) {
            // Ignore . and ..
            if (strcmp(".", entry->d_name) == 0 ||
                strcmp("..", entry->d_name) == 0)
                continue;

            // check for inode match
            if (st.st_ino == opt->inode) {
                int bytes = snprintf(out->buffer + out->buf_len,
                                     MAX_BUF_LEN - out->buf_len,
                                     "%s\n",
                                     entry->d_name);
                out->buf_len += bytes;
            } 

            // Recurse
            find_files(opt, entry->d_name);
        } else {
            // check for inode match
            if (st.st_ino == opt->inode) {
                int bytes = snprintf(out->buffer + out->buf_len,
                                     MAX_BUF_LEN - out->buf_len,
                                     "%s\n",
                                     entry->d_name);
                out->buf_len += bytes;

                if (opt->verbose)
                    printf("Found inode match: %s\n", entry->d_name);
            } 
        }
    }

    chdir("..");
    closedir(dp);

    return out;
}

// TODO: add to interface, so command can be approached from a file name
//  rather than inode.
// syswiz -f file
//  information about the file
//  if hardlinked, auto-searching for other fs locations
//  ...
//  eventually some kind of top-like dynamic view following file changes?
//   tail -f + stat + top ?

// TODO: invoking syswiz with no arguments should start an interactive system.
//  So syswiz can be used either as a single-execution command fitting with
//  the UNIX pipeline model or it can be used as an interactive system
//  diagnosic.
// Slightly ambitious, but if the basic double-structure is put in place, then
//  this could serve as a good place to put utility routines as they're
//  acquired.
// I suppose the tricky part here is to handle updating changes in displayed
//  information during interactive mode. So each command has to work with a
//  similar output structure so it can be appropriately formated.

// TODO: from a design standpoint, what about basing the interface around the
//  concept of identifying a single interesting starting structure?

// A file, an inode, a process, a network port, a network connection, and so
//  on ...

// Perhaps the interactive mode involves combining streams of these target-
//  oriented commands.


