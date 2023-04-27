#include "fs.h"
#include <stdio.h>

/**
 * read the contents of an entire file into a string. the string containing the
 * file contents is dynamically allocated.
 *
 * @param   path: the path that points to the file
 *
 * @return  the file contents, or nullptr on error
 *
 * @note    since the returned string is dynamically allocated, its memory
 *          needs to be freed manually.
 */
char *
fs_read_to_str (const char *path)
{
    FILE *fp;
    char *buf;
    usize len;

    if (path && (fp = fopen (path, "r"))) {
        fseek (fp, 0, SEEK_END);
        len = ftell (fp);
        fseek (fp, 0, SEEK_SET);

        buf = smalloc (len + 1);

        fread (buf, sizeof *buf, len, fp);
        buf[len] = '\0';

        fclose (fp);
    } else {
        return nullptr;
    }

    return buf;
}

/**
 * write a string to a file.
 *
 * @param   path: the path to the file
 * @param   content: the string to write
 *
 * @return  false on error, true on success
 */
bool
fs_write_file (const char *path, const char *content)
{
    FILE *fp;

    if (path && content && (fp = fopen (path, "w+"))) {
        if (fputs (content, fp) == EOF)
            return false;
        fclose (fp);
    } else {
        return false;
    }

    return true;
}
