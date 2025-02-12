 #include <stdio.h>
#include <string.h>

void check_comment(const char* line) {
    if (strstr(line, "//")) {
        printf("Single-line comment detected.\n");
    } else if (strstr(line, "/*") && strstr(line, "*/")) {
        printf("Multi-line comment detected.\n");
    } else {
        printf("No comment detected.\n");
    }
}

int main() {
    char line[256];
    printf("Enter a line of code: ");
    fgets(line, sizeof(line), stdin);

    check_comment(line);

    return 0;
}

