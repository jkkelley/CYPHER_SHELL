/* golden_configMap.c */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

// stdio.h
// fclose() - closes file
// fputs()  - Writes byte string to a file stream
// fread()  - read from a file
// fopen()  - opens file

// stdlib.h
// EXIT_FAILURE - Marco inidicating unsuccessful
// program failure
// NULL         - Macro represting a null pointer constant

// limits.h
// CONST PATH_MAX - hands out the max bytes for
// a directory path

// unistd.h
// getcwd() - gets the current working dir

int main()
{

    // 1. Create the bucket (buffer)
    char local_path[PATH_MAX];

    // 2. Call the function
    // Pass the buffer and its size (1024)
    // max of 1023 visible chars
    if (getcwd(local_path, sizeof(local_path)) != NULL)
    {
        printf("\n\nCurrent dir: %s\n", local_path);
    }
    else
    {
        perror("getcwd() error");
    }


    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/test123.txt", local_path);

    // TODO: remove when done
    printf("file_name: %s\n", full_path);
    printf("--- # ---\n\n\n");

    int is_ok = EXIT_FAILURE;

    FILE* fp = fopen(full_path, "w+");
    if (!fp)
    {
        perror("File opening failed");
        return is_ok;
    }

    fputs("apiVersion: \n", fp);
    fputs("kind: \n", fp);
    fputs("metadata: \n  ", fp);
    fputs("\n", fp);
    fputs("spec:  \n", fp);
    rewind(fp);
    
    int c;
    // Read until EOF is hit
    while ((c = fgetc(fp)) != EOF)
    {
        putchar(c);
    }

    // Always close what you open
    fclose(fp);

    return 0;
}
