#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void count_characters_words_lines(FILE *file) {
    int characters = 0, words = 0, lines = 0;
    char ch, prev = '\0';

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if ((ch == ' ' || ch == '\n' || ch == '\t') && (prev != ' ' && prev != '\n' && prev != '\t')) {
            words++;
        }

        prev = ch;
    }

    if (prev != ' ' && prev != '\n' && prev != '\t') {
        words++;  // Count the last word if file doesn't end with a space
    }

    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);
}

int main() {
    FILE *file;
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    count_characters_words_lines(file);

    fclose(file);
    return 0;
}

