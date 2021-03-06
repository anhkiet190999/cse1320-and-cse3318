#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw6_fns.h"

#define MAX_CHARS_PER_LINE 200

typedef struct _Business{
    char business[70];
    char address[40];
    char contact[60];
} Business;

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("passing arguments incorrectly!!\n");
        printf("usage: fileExe fileNmae match_name\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("could not open the file\n");
        exit(EXIT_FAILURE);
    }
    
    char buff[MAX_CHARS_PER_LINE+1];
    Business *b;
    int count =0;

    b = malloc(1*sizeof(Business));
    if(b == NULL){
        printf("out of memory!\n");
        exit(EXIT_FAILURE);
    }

    /* char *match_name;
    match_name = malloc((strlen(argv[2])+1) * sizeof(char));
    if(match_name == NULL){
        printf("out of memory!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(match_name, argv[2]); */

    //skip the first line because it is the title line, and also check whether the file is null
    if(fgets(buff, sizeof(buff), fp) == NULL){
        printf("could not read the file\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(buff, sizeof(buff), fp) != NULL){
        getBusiness(b[count].business, buff);
        getAddress(b[count].address, buff);
        getContact(b[count++].contact, buff);
        b = realloc(b, (count+1)*sizeof(Business));
    }

    for(int i=0; i<count;i++){
        printf("Business: %s\n", b[i].business);
        printf("Address: %s\n", b[i].address);
        printf("Contact: %s\n\n", b[i].contact);
    }

    char **match_business_list; //string array
    int count_match = 0;
    match_business_list = malloc(1*sizeof(char*));
    if(match_business_list == NULL){
        printf("out of memory!\n");
        free(match_business_list);
        exit(EXIT_FAILURE);
    }

    //char *match_business;

    //it is important to know the difference between static string and dynamic string. 
    // in this case, b[i].business is static string, while match_business is an dynamic string.
    // use strcpy for static string. and use "=" for dynamic string. 

    for(int i=0; i<count;i++){
        if(strstr(b[i].business, argv[2]) != NULL){
            match_business_list[count_match] = malloc((strlen(b[i].business)+1)*sizeof(char));

            // match_business = b[i].business; //didn't work. 
            //strcpy(match_business, b[i].business); // copy a string to a pointer

            //strcpy(match_business_list[count_match++],match_business); //didn't work. 
           // match_business_list[count_match++] = match_business; //tell a pointer to point the same address of a pointer
           strcpy(match_business_list[count_match++], b[i].business);

            match_business_list = realloc(match_business_list, (count_match+1)*sizeof(char*));

        }
    }

    if(count_match == 0){
        printf("there is no matching name with %s\n", argv[2]);
    } else{
    printf("there are %d business that have the name match %s: \n",count_match, argv[2]);
        for(int i=0; i<count_match; i++){
            printf("%s\n", match_business_list[i]);
        }
    }
    
   // free(match_name);
    free(b);

    for(int i=0; i <count_match; i++){
        free(match_business_list[i]);
    }
    free(match_business_list);
    fclose(fp);

    return EXIT_SUCCESS;
}