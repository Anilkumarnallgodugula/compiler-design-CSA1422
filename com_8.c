 #include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

struct Symbol {
    char name[50];
    char type[50];
    int address;
};

struct SymbolTable {
    struct Symbol symbols[SIZE];
    int count;
} table;

void insert_symbol(char* name, char* type, int address) {
    int i;
    for (i = 0; i < table.count; i++) {
        if (strcmp(table.symbols[i].name, name) == 0) {
            printf("Symbol '%s' already exists.\n", name);
            return;
        }
    }
    strcpy(table.symbols[table.count].name, name);
    strcpy(table.symbols[table.count].type, type);
    table.symbols[table.count].address = address;
    table.count++;
    printf("Symbol '%s' inserted.\n", name);
}

void display_symbols() {
    int i;
    printf("\nSymbol Table:\n");
    printf("Name\tType\tAddress\n");
    for (i = 0; i < table.count; i++) {
        printf("%s\t%s\t%d\n", table.symbols[i].name, table.symbols[i].type, table.symbols[i].address);
    }
}

void search_symbol(char* name) {
    int i;
    for (i = 0; i < table.count; i++) {
        if (strcmp(table.symbols[i].name, name) == 0) {
            printf("Symbol found: %s, Type: %s, Address: %d\n", table.symbols[i].name, table.symbols[i].type, table.symbols[i].address);
            return;
        }
    }
    printf("Symbol '%s' not found.\n", name);
}

void delete_symbol(char* name) {
    int i, j;
    for (i = 0; i < table.count; i++) {
        if (strcmp(table.symbols[i].name, name) == 0) {
            for (j = i; j < table.count - 1; j++) {
                table.symbols[j] = table.symbols[j + 1];
            }
            table.count--;
            printf("Symbol '%s' deleted.\n", name);
            return;
        }
    }
    printf("Symbol '%s' not found.\n", name);
}

int main() {
    int choice, address;
    char name[50], type[50];

    table.count = 0;

    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert\n2. Display\n3. Search\n4. Delete\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter symbol name: ");
                scanf("%s", name);
                printf("Enter symbol type: ");
                scanf("%s", type);
                printf("Enter symbol address: ");
                scanf("%d", &address);
                insert_symbol(name, type, address);
                break;
            case 2:
                display_symbols();
                break;
            case 3:
                printf("Enter symbol name to search: ");
                scanf("%s", name);
                search_symbol(name);
                break;
            case 4:
                printf("Enter symbol name to delete: ");
                scanf("%s", name);
                delete_symbol(name);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

