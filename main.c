// TODO: be able to set a custom directory to save files to
#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include <string.h>

#define GRATITUDE_FILE_MAX_LENGTH 27
#define QUIT 'q'

// This will create a file that contains the current date and will be used
// to store contents of the gratitude entry
FILE * create_new_file() {
    FILE *fp = NULL;

    char filename[GRATITUDE_FILE_MAX_LENGTH];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // filename should be the time when we're recording this entry
    strftime(filename, sizeof(filename)-1, "gratitude-%m-%d-%Y-%H:%M", &tm);

    fp = fopen(filename, "w+");

    return fp;
}

// This function will create an entry with a number associated to it
// ex: 1.) I'm grateful for my amazing C skills (jk)
char *create_gratitude_entry_str(char *buffer, int buffer_length, int count) {
    char *entry = malloc(4 + buffer_length + 1); // 4 for "1.) ", 1 for \0

    sprintf(entry, "%d", count);
    strcat(entry, ".) ");

    // TODO: figure out if there's a more optimized way to do this
    // because right now we're re-reading from the start again
    strcat(entry, buffer);

    return entry;
}

int main() {

    FILE *fp = create_new_file();

    char *buffer = NULL;
    int line_size; // # of characters in line
    size_t size_bytes; // # of bytes allocated
    int running = 1;
    int gratitude_entry_count = 0;

    printf("What are things you are grateful for today? ('q' to quit)\n\n");

    while (1) {
        printf("%d.) ", ++gratitude_entry_count);
        line_size = getline(&buffer, &size_bytes, stdin);


        if (buffer[0] == QUIT) {
            printf("Thanks for being grateful! See ya tomorrow\n");
            break;
        }

        if (-1 != line_size) {
            char *entry = create_gratitude_entry_str(buffer, line_size, gratitude_entry_count);
#ifdef DEBUG
            printf("# of bytes %zu", size_bytes);
            puts(entry);
#endif
            fputs(entry, fp);
        }
#ifdef DEBUG
        else {
            printf("No line read...\n");
        }
#endif
    }

    free(buffer);
    fclose(fp);

    return 0;
}