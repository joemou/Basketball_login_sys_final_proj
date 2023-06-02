#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define watch_int(x) printf(#x " is %d\n", x)
#define watch_string(x) printf(#x " is %s\n", x)
#define debug printf("Debug line %d\n", __LINE__)

char *read_json_to_str(char *file_name){
    FILE *file = fopen(file_name, "r");

    fseek (file , 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    char *json_file = (char*) malloc(sizeof(char) * size);
    fread(json_file, 1, size, file);

    fclose(file);
    
    return json_file;
}

int main() {

    char *name[] = {"Mo Bamba", "Malik Beasley", "Troy Brown Jr.", "Max Christie", "Anthony Davis", "Wenyen Gabriel", "Rui Hachimura", "LeBron James", "Scotty Pippen Jr.", "Austin Reaves", "D'Angelo Russell", "Dennis Schröder", "Cole Swider", "Jarred Vanderbilt", "Lonnie Walker IV"};
    int game_played[] = {9, 26, 76, 41, 56, 68, 33, 55, 6, 64, 17, 67, 7, 26, 56};
    float three_pt[] = {.313, .353, .381, .419, .563, .596, .296, .321, .333, .383, .414, .329, .375, .303, .365};
    float pt_per_round[] = {3.7, 11.1, 7.1, 3.1, 25.9, 5.5, 11.2, 28.9, 2.3, 13.0, 17.4, 12.4, 1.3, 7.2, 11.7};

    char *json_file = read_json_to_str("data.json");

    cJSON *edit_obj = cJSON_Parse(json_file);
    cJSON *team = cJSON_GetObjectItem(edit_obj, "Basket_Ball_Teams");
    for(int i = 0; i < 1; ++i){
        cJSON *authed_team = cJSON_GetArrayItem(team, i);
        cJSON_AddArrayToObject(authed_team, "Players");
        cJSON *players = cJSON_GetObjectItem(authed_team, "Players");
        for(int j = 0; j < 15; ++j){
            cJSON *player = cJSON_CreateObject();
            cJSON_AddStringToObject(player, "Player Name", name[j]);
            cJSON_AddNumberToObject(player, "game_played", game_played[j]);
            cJSON_AddNumberToObject(player, "three_pt", three_pt[j]);
            cJSON_AddNumberToObject(player, "pt_per_round", pt_per_round[j]);
            
            cJSON_AddItemToArray(players, player);
        }
        printf("%s", cJSON_Print(edit_obj));
    }

    FILE *file = fopen("data.json", "w");
    fputs(cJSON_Print(edit_obj), file);
    fclose(file);

    free(json_file);

    return 0;
}
