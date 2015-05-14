
#define MAX_PATH_LEN    2048

typedef
struct options_struct {
    int find_files_from_inode;
    int inode_num;
    int path_set;
    char path[MAX_PATH_LEN];
} opt_t;

/* Parses the command line and fills the options structure, 
 * returns non-zero on error */
int parse_options(opt_t *opts, int argc, char **argv);

int main(int argc, char **argv) {
    opt_t opts;
    if (parse_options(&opts, argc, argv)) {
        return 1;
    } 

    return 0;
}

int parse_options(opt_t *opts, int argc, char **argv) {
    while ((o = getopt (argc, argv, "f:p:")) != -1) {
        switch (o) {
            case 'f':
                opts->find_files_from_inode = 1;
                break;
            case 'p':
                opts->path_set = 1;
                strncpy(opts->path, optarg, strlen(optarg))
                break;
           default:
                printf("Unrecognized arg: %s\n", o);
                return 1;
       }
    }

    if (opts->path_set) {
        if (!verify_path(opt->path))
            printf("Invalid path: %s\n", opts->path);
            return 1;
    }

    return 0;
}

int verify_path(char *path) {
    DIR* dir = opendir("mydir");
    if (dir) {
        /* Directory exists. */
        closedir(dir);
    }
    else if (ENOENT == errno) {
        /* Directory does not exist. */
    }
    else {
        /* opendir() failed for some other reason. */
    }
}
