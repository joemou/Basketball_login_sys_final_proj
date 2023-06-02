
#include <stdio.h>
#include "cJSON.h"

#define debug printf("Debug line %d\n", __LINE__)
  
int main() {

    char *name;
    int ptr;
    FILE *fptr = fopen("test data.json", "w");
    while(scanf("%s %d", name, &ptr) != EOF){
        cJSON *json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "name", name);
        cJSON_AddNumberToObject(json, "Points", ptr);
        fputs(cJSON_Print(json), fptr);
        cJSON_Delete(json);
    }
    fclose(fptr);


   return 0;
}