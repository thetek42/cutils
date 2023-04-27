#ifndef FS_H_
#define FS_H_

#include "common.h"

char *fs_read_to_str (const char *path); /* read the contents of an entire file into a string */
bool fs_write_file (const char *path, const char *content); /* write a string to a file */

#endif // FS_H_
