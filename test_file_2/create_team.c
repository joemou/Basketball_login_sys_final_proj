#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define watch_int(x) printf(#x " is %d\n", x)
#define watch_string(x) printf(#x " is %s\n", x)
#define debug printf("Debug line %d\n", __LINE__)

int main() {

    char *team_name[] = {"Los Angeles Lakers", "Golden State Warriors"};

    FILE *file = fopen("data.json", "w");

    cJSON *json_object = cJSON_CreateObject();
    cJSON_AddItemToObject(json_object, "Basket_Ball_Teams", cJSON_CreateArray());
    cJSON *team_array = cJSON_GetObjectItem(json_object, "Basket_Ball_Teams");
    for(int i = 0; i < 2; i++){
        cJSON *add_team = cJSON_CreateObject();
        cJSON_AddStringToObject(add_team, "Team Name", team_name[i]);
        cJSON_AddItemToArray(team_array, add_team);
    }

    char *json_string = cJSON_Print(json_object);

    printf("%s", json_string);

    fputs(json_string, file);

    fclose(file);

    return 0;
}
