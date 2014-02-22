#include "files.h"

size_t get_file_size(const char * file_name) {
    struct stat sb;
    if (stat (file_name, & sb) != 0) {
        fprintf(stderr, "'stat' failed for '%s': %s.\n", file_name, strerror (errno));
        exit(EXIT_FAILURE);
    }
    return sb.st_size;
}

char* read_file(const char* file_name)
{
    size_t s;
    char * contents;
    FILE * f;
    size_t bytes_read;
    int status;

    s = get_file_size (file_name);
    contents = malloc (s + 1);
    if (! contents) {
        fprintf (stderr, "Not enough memory.\n");
        exit (EXIT_FAILURE);
    }

    f = fopen (file_name, "r");
    if (! f) {
        fprintf (stderr, "Could not open '%s': %s.\n", file_name,
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    bytes_read = fread (contents, sizeof (char), s, f);
    if (bytes_read != s) {
        fprintf (stderr, "Short read of '%s': expected %lu bytes "
                 "but got %lu: %s.\n", file_name, (unsigned long)s, (unsigned long)bytes_read,
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    status = fclose (f);
    if (status != 0) {
        fprintf (stderr, "Error closing '%s': %s.\n", file_name,
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    return contents;
}
