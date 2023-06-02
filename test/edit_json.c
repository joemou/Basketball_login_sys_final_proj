#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

// cJSON *read_json_to_str(char *file_name) {
//     FILE *file = fopen(file_name, "r");
//     printf("hi");

//     fseek (file , 0, SEEK_END);
//     int size = ftell(file);
//     // printf("%d", size);
//     rewind(file);
//     char *json_file = (char*) calloc(size, sizeof(char));
//     fread(json_file, 1, size, file);
//     // printf("%s", json_file);
//     cJSON *tmp = cJSON_Parse(json_file);
//     free(json_file);

//     fclose(file);
    
//     return tmp;
// }

char *read_json_to_str(char *file_name) {
    FILE *file = fopen(file_name, "r");
    // printf("hi");

    fseek (file , 0, SEEK_END);
    int size = ftell(file);
    // printf("%d", size);
    rewind(file);
    char *json_file = (char*) calloc(size, sizeof(char));
    fread(json_file, 1, size, file);
    // printf("%s", json_file);
    // cJSON *tmp = cJSON_Parse(json_file);
    // free(json_file);

    fclose(file);
    
    return json_file;
}

void json_create_new_team(char *new_team) {
    char *data = read_json_to_str("data.json");
    cJSON *team = cJSON_Parse(data);
    printf("%s", cJSON_Print(team));
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

int main(){
    json_create_new_team("lol");
    return 0;
}