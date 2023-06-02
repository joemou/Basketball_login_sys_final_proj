#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define watch_int(x) printf(#x " is %d\n", x)
#define watch_string(x) printf(#x " is %s\n", x)
#define debug printf("Debug line %d\n", __LINE__)

int main() {

    FILE *file = fopen("data.json", "r");

    fseek (file , 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    char *json_file = (char*) malloc(sizeof(char) * size);
    fread(json_file, 1, size, file);

    cJSON *edit_obj = cJSON_Parse(json_file);
    cJSON *team = cJSON_GetObjectItem(edit_obj, "Basket_Ball_Teams");
    cJSON *authed_team = cJSON_GetArrayItem(team, 0);
    watch_string(cJSON_Print(authed_team));

    fclose(file);
    free(json_file);

    return 0;
}
