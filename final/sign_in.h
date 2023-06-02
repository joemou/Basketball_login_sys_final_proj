int hash(char *str);
void insert_user(struct hash_table *table, struct user *user);
int find_user(struct hash_table *table);
void create_user(struct hash_table *table);
void save_users(struct hash_table *table, char *filename);
void load_users(struct hash_table *table, char *filename);