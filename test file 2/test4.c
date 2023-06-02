#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define debug printf("Debug line %d\n", __LINE__)

int main() {
    // Step 1: Create a cJSON object representing the JSON array
    cJSON *jsonArray = cJSON_CreateObject();
    cJSON_AddArrayToObject(jsonArray, "myArray");

    // Step 2: Load existing JSON array from file or create an empty array
    // FILE *file = fopen("data.json", "r");
    // if (file != NULL) {
    //     fseek(file, 0, SEEK_END);
    //     long fileSize = ftell(file);
    //     fseek(file, 0, SEEK_SET);
    //     char *jsonData = malloc(fileSize + 1);
    //     fread(jsonData, 1, fileSize, file);
    //     fclose(file);

    //     jsonArray = cJSON_Parse(jsonData);
    //     free(jsonData);
    // }

    // Step 3: Append JSON object to the existing JSON array
    cJSON *newObject = cJSON_CreateObject();
    cJSON_AddStringToObject(newObject, "name", "John");
    cJSON_AddNumberToObject(newObject, "age", 25);
    cJSON_AddItemToArray(jsonArray, newObject);
    // cJSON_GetObjectItem();

    // Step 4: Write updated JSON array back to file or store as a string
    FILE *file = fopen("data.json", "w");
    if (file != NULL) {
        char *updatedData = cJSON_Print(jsonArray);
        printf("%s", cJSON_Print(jsonArray));
        fwrite(updatedData, 1, strlen(updatedData), file);
        fclose(file);
        free(updatedData);
    }

    // Clean up cJSON objects
    cJSON_Delete(jsonArray);

    return 0;
}
