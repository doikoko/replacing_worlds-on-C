#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 50
#define MAX_DICTIONARY_LENGTH 10000
#define MAX_ROW_LENGTH 2000
#define MAX_USER_INPUT_LENGTH 20000

typedef struct {
    char *key;
    char *value;
} Dict;
Dict dictionary[MAX_DICTIONARY_LENGTH];
int dictionary_size = 0;

void read_dictionary(char *row);
void replace_words(char *user_input);

int main(int argc, char *argv[]){
    char *row = (char*)malloc(sizeof(char) * MAX_ROW_LENGTH);
        if(row == NULL){
        printf("Memory error");
        exit(-1);
    }

    read_dictionary(row);
    printf("Enter word/text to replace(max length is %d)\n", MAX_USER_INPUT_LENGTH);
    
    char *user_input = (char*)malloc(sizeof(char) * MAX_USER_INPUT_LENGTH);
    if(user_input == NULL){
        printf("Memory error");
        exit(-1);
    }

    while(user_input[0] == '\0') {
        fgets(user_input, MAX_USER_INPUT_LENGTH, stdin);
        user_input[strcspn(user_input, "\n")]  = '\0';
    }

    replace_words(user_input);
    printf("result is: %s\n", user_input);

    for(int i = 0; i < MAX_DICTIONARY_LENGTH; i++){
        free(dictionary[i].key);
        free(dictionary[i].value);
    }
    
    free(row);
    return 0;
}

void read_dictionary(char *row){    
    char *file_name = (char*)malloc(sizeof(char) * MAX_FILE_NAME_LENGTH);
    printf("Enter file name: ");
    fgets(file_name, sizeof(char) * MAX_FILE_NAME_LENGTH, stdin);
    file_name[strcspn(file_name, "\n")] = '\0';
    
    FILE *dict_file = fopen(file_name, "r");
    
    if (dict_file == NULL){
        perror("File open error ");
        exit(-1);
    }
    

    while (fgets(row, MAX_ROW_LENGTH, dict_file)){
        row[strcspn(row, "\n")] = '\0';
        char *separator = strchr(row, '\t');
        
        if(separator != NULL){
            *separator = '\0';     
            dictionary[dictionary_size].key = strdup(row);
            dictionary[dictionary_size].value = strdup(separator + 1);
            dictionary_size++;
        } else {
            perror("incorrect dictionary");
            exit(-1);
        }
    }
    
    fclose(dict_file);
    free(file_name);
}

void replace_words(char *user_input) {
    char *result = (char*)malloc(sizeof(char) * (MAX_USER_INPUT_LENGTH * 2));
    
    if (result == NULL) {
        perror("Memory error");
        exit(1);
    }

    char *current_pos = user_input;
    
    for (int i = 0; i < dictionary_size; i++) {
        char *next_pos;
        while ((next_pos = strstr(current_pos, dictionary[i].key)) != NULL) {
            strncat(result, current_pos, next_pos - current_pos);
            strcat(result, dictionary[i].value);
            current_pos = next_pos + strlen(dictionary[i].key);
        }
    }
    strcat(result, current_pos);
    strcpy(user_input, result);

    free(result);
}