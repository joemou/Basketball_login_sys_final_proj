#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10000

struct user {
    char username[50];
    char password[50];
    // other fields here
};

struct hash_table {
    int size;
    struct user **users;
};

int hash(char *str) {
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

void create_user(struct hash_table *table, char *username, char *password) {
    struct user *new_user = malloc(sizeof(struct user));
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    insert_user(table, new_user);
}

void save_users(struct hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file.\n");
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

int main() {
    struct hash_table table;
    table.size = HASH_SIZE;
    table.users = malloc(sizeof(struct user *) * table.size);
    memset(table.users, 0, sizeof(struct user *) * table.size);

    // create users from team_mapping dictionary
    char *team_mapping[16] = {
        "Boston_Celtics",
        "Brooklyn_Nets",
        "New_York_Knicks",
        "Philadelphia_76ers",
        "Toronto_Raptors",
        "Chicago_Bulls",
        "Detroit_Pistons",
        "Milwaukee_Bucks",
        "Charlotte_Hornets",
        "Miami_Heat",
        "Denver_Nuggets",
        "Golden_State_Warriors",
        "Los_Angeles_Clippers",
        "Los_Angeles_Lakers",
        "Houston_Rockets",
        "Memphis_Grizzlies",
        "San_Antonio_Spurs"};

    for (int i = 0; i < 16; i++) {
        char username[50];
        sprintf(username, "%s", team_mapping[i]);
        char password[50] = "password";  // Set a default password for all users
        create_user(&table, username, password);
    }

    // save users to file
    save_users(&table, "users.dat");

    return 0;
}
