#define FUSE_USE_VERSION 28
#define _GNU_SOURCE
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#define MAX_BUF 4096

char helloContent[MAX_BUF] = "Hello World";

static int fs_getattr(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));
    stbuf->st_uid = getuid();
    stbuf->st_gid = getgid();
    stbuf->st_atime = stbuf->st_mtime = stbuf->st_ctime = time(NULL);

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }

    if (strcmp(path, "/hello.txt") == 0) {
        stbuf->st_mode = S_IFREG | 0644;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(helloContent);
        return 0;
    }
    return -ENOENT;
}

static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "hello.txt", NULL, 0);

    return 0;
}

static int fs_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, "/hello.txt") == 0)
        return 0;

    return -ENOENT;
}

static int fs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
    (void)fi;
    char *content = NULL;
    size_t len;

    if (strcmp(path, "/hello.txt") == 0) {
        content = helloContent;
    } else {
        return -ENOENT;
    }

    len = strlen(content);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, content + offset, size);
    } else {
        size = 0;
    }

    return size;
}

static int fs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void)offset;
    (void)fi;

    if (strcmp(path, "/hello.txt") == 0) {
        strcpy(helloContent, buf);
    } else {
        return -ENOENT;
    }
    return size;
}

static struct fuse_operations fs_operation = {
    .getattr = fs_getattr,
    .readdir = fs_readdir,
    .read = fs_read,
    .write = fs_write,
    .open = fs_open
};

int  main(int  argc, char *argv[]) {
    return fuse_main(argc, argv, &fs_operation, NULL);
}