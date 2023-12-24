// Written by Alicia M. Chun for the 2023 Advent of Code Day 2 Part 1 
// Completed Dec. 23, 2023
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid_pull(char *tok) {
    char *sep = " ";
    char *string = tok + 1; 
    char *save_pointer = NULL;
    int n = atoi(strtok_r(string, sep, &save_pointer));
    char *color = strtok_r(NULL, sep, &save_pointer); 
    if(color[strlen(color) - 1] == '\n') {
        color[strlen(color) - 1] = 0;
    }
    if(strcmp(color, "red") == 0 && n > 12) {
        printf("BAD: red");
        return 0;
    }
    if(strcmp(color, "blue") == 0 && n > 14) {
        printf("BAD: blue");
        return 0;
    }
    if(strcmp(color, "green") == 0 && n > 13) {
        printf("BAD: green");
        return 0; 
    }
    printf("color, %s", color);
    printf("|");
    return 1; 
}

int parse_set(char *set) {
    char *sep = ","; 
    char *token; 
    char *save_pointer = NULL;
    token = strtok_r(set, sep, &save_pointer);
    int valid = 1; 
    while(token != NULL) {
        // 12 red cubes, 13 green cubes, and 14 blue cubes
        valid = valid && valid_pull(token);
        token = strtok_r(NULL, sep, &save_pointer);
    }
    return valid;
}

int parse_line(char *line) {
    char *save_pointer = NULL; 
    char *sep = ";";
    char *token; 
    int valid; 
    token = strtok_r(line, sep, &save_pointer);
    while(token != NULL) {
        valid = valid && parse_set(token);
        token = strtok_r(NULL, sep, &save_pointer);
    }
    return valid;
}

int main(int argc, char *argv[]) {
    int sum = 0;  
    if(argc > 1) {
        FILE *fp; 
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("Unable to access file");
            exit(1);
        }
        char line[1000];
        int game_num = 0; 
        int valid;
        int i;
        while(fgets(line, 1000, fp) != NULL) {
            // printf("line: %s", line);
            for(int i = 0; i < 100; i++) {
                if(line[i] == ':') {
                    break; 
                }
            }
            i = 5;
            game_num = 0; 
            while(line[i] >= 48 && line[i] <= 57) {
                game_num = (game_num * 10) + (line[i] - 48);
                i = i + 1; 
            }
            printf("%d\n", game_num);
            char *sublime = line + i + 1; //LOL
            printf("sublime: %s", sublime);
            valid = parse_line(sublime);
            if(valid) {
                sum = sum + game_num;            
            }
            printf("  sum: %d\n", sum);
        }
    }
}