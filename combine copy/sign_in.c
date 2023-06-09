#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "edit_json.h"
#include "sign_in.h"

int hash(const char *str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum % HASH_SIZE;
}

void insert_user(struct hash_table *table, struct user *user) {
    int index = hash(user->username);
    while (table->users[index] != NULL) {
        index = (index + 1) % table->size;
    }
    table->users[index] = user;
}

void insert_new_user(struct hash_table *table, struct user *user) {
    int index = hash(user->username);
    while (table->users[index] != NULL) {
        index = (index + 1) % table->size;
    }
    table->users[index] = user;
    json_create_new_team(user->username);
}

int find_user(struct hash_table *table, const char *username, const char *password) {
    int index = hash(username);
    while (table->users[index] != NULL) {
        if (strcmp(table->users[index]->username, username) == 0 && strcmp(table->users[index]->password, password) == 0) {
            return 1;
        }
        index = (index + 1) % table->size;
    }
    return 0;
}

// not used
void create_user(struct hash_table *table) {
    while (1) {
        char username[50];
        char password[50];
        char password2[50];
        // printf("Sign Up\n");
        // printf("Enter username: ");
        // scanf("%s", username);
        // printf("Enter password: ");
        // scanf("%s", password);
        // printf("Enter password again: ");
        // scanf("%s", password2);
        if (strcmp(password, password2) == 0) {
            struct user *new_user = malloc(sizeof(struct user));
            strcpy(new_user->username, username);
            strcpy(new_user->password, password);
            insert_new_user(table, new_user);
            printf("Sign Up successful!\n\n");
            break;
        } else {
            printf("The password entered twice is different\n\n");
        }
    }
}

void save_users(struct hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        g_print("Error opening file.\n");
        return;
    }

    // write the number of users
    int count = 0;
    for (int i = 0; i < table->size; i++) {
        if (table->users[i] != NULL) {
            count++;
        }
    }
    fwrite(&count, sizeof(int), 1, fp);

    // write each user to file
    for (int i = 0; i < table->size; i++) {
        if (table->users[i] != NULL) {
            fwrite(table->users[i], sizeof(struct user), 1, fp);
        }
    }

    fclose(fp);
}

void load_users(struct hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // read the number of users
    int count;
    fread(&count, sizeof(int), 1, fp);

    // read each user from file and insert into hash table
    for (int i = 0; i < count; i++) {
        struct user *new_user = malloc(sizeof(struct user));
        fread(new_user, sizeof(struct user), 1, fp);
        insert_user(table, new_user);
    }

    fclose(fp);
}

/*
// int main() {
//     struct hash_table table;
//     table.size = HASH_SIZE;
//     table.users = malloc(sizeof(struct user *) * table.size);
//     memset(table.users, 0, sizeof(struct user *) * table.size);

//     // load users from file
//     load_users(&table, "users.dat");

//     // create some sample users
//     int choice, Login_successful = 0;
//     while (Login_successful == 0) {
//         printf("1: Sign up\n2: Login\n");
//         scanf(" %d", &choice);
//         if (choice == 1) {
//             create_user(&table);
//         } else {
//             // authenticate user
//             if (find_user(&table)) {
//                 printf("Login successful!\n\n");
//                 Login_successful = 1;
//             } else {
//                 printf("Login failed. Invalid username or password.\n\n");
//             }
//         }
//     }

//     // save users to file before exiting
//     save_users(&table, "users.dat");

//     return 0;
// }

*/