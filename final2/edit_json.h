
typedef struct cJSON cJSON;

// reads json file
char *read_json_to_str(char *file_name);

void json_create_new_team(char *new_team);

cJSON *find_team(const char *username);