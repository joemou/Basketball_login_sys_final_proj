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

int hash(const char *str);
void insert_user(struct hash_table *table, struct user *user);
int find_user(struct hash_table *table, const char *username, const char *password);
void create_user(struct hash_table *table);
void save_users(struct hash_table *table, char *filename);
void load_users(struct hash_table *table, char *filename);