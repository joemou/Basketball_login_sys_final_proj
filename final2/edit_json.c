#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "edit_json.h"

char *read_json_to_str(char *file_name) {
    FILE *file = fopen(file_name, "r");

    fseek (file , 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    char *json_file = (char*) calloc(size, sizeof(char));
    fread(json_file, 1, size, file);

    fclose(file);
    
    return json_file;
}

void json_create_new_team(char *new_team) {
    char *data = read_json_to_str("data.json");
    cJSON *team = cJSON_Parse(data);
    cJSON *team_array = cJSON_GetObjectItem(team, "Basket_Ball_Teams");
    cJSON *tmp = cJSON_CreateObject();
    cJSON_AddStringToObject(tmp, "Name", new_team);
    cJSON_AddArrayToObject(tmp, "Players");
    cJSON_AddItemToArray(team_array, tmp);
    
    FILE *file = fopen("data.json", "w");
    fputs(cJSON_Print(team), file);
    fclose(file);
    cJSON_free(team);
    cJSON_free(team_array);
    cJSON_free(tmp);
}

cJSON *find_team(const char *username) {
    char *data = read_json_to_str("data.json");
    cJSON *team = cJSON_Parse(data);
    cJSON *team_array = cJSON_GetObjectItem(team, "Basket_Ball_Teams");
    int size = cJSON_GetArraySize(team_array);
    cJSON *tgt_team;
    for(int i = 0; i < size; i++) {
        tgt_team = cJSON_GetArrayItem(team_array, i);
        char *tmp_name = cJSON_GetStringValue(cJSON_GetObjectItem(tgt_team, "Name"));
        if(strcmp(tmp_name, username) == 0) break;
    }
    cJSON *tgt_team_players_array = cJSON_GetObjectItem(tgt_team, "Players");

    return tgt_team_players_array;
}