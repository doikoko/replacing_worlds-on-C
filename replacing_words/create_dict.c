#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 50
#define MAX_LENGTH 1000
int main(){
    char *file_name = (char*)malloc(sizeof(char) * MAX_FILE_NAME_LENGTH);
    printf("Enter file name: ");
    fgets(file_name, sizeof(char) * MAX_FILE_NAME_LENGTH, stdin);
    file_name[strcspn(file_name, "\n")] = '\0';
    
    FILE *f = fopen(file_name, "w");
    
    if (f == NULL){
        perror("File open error ");
        exit(-1);
    }

    char *start = (char*)malloc(MAX_LENGTH);
    char *end = (char*)malloc(MAX_LENGTH);
        
    while (1){
        printf("enter start value (empty to exit): ");
        fgets(start, MAX_LENGTH, stdin);
        start[strcspn(start, "\n")] = '\0';
        
        if (strcmp(start, "") == 0) {
            break; 
        }
        printf("enter end value: ");
        fgets(end, MAX_LENGTH, stdin);
        end[strcspn(end, "\n")] = '\0';
        
        fprintf(f, "%s\t%s\n", start, end);
    }
    fclose(f);
    free(file_name);
    return 0;    
}