// Written by Alicia M. Chun for the 2023 Advent of Code Day 2 Part 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Color {
    int red; 
    int green;
    int blue;
};

void set_power(char *tok, struct Color *min_color) {
    char *sep = " ";
    char *string = tok + 1; 
    char *save_pointer = NULL;
    int n = atoi(strtok_r(string, sep, &save_pointer));
    char *color = strtok_r(NULL, sep, &save_pointer); 
    if(color[strlen(color) - 1] == '\n') {
        color[strlen(color) - 1] = 0;
    }
    printf("n: %d\n", n);
    printf("color: %s\n", color);
    if(strcmp(color, "blue") == 0 && n > min_color->blue) { 
        min_color->blue = n;
        printf("Changing Blue, min_color->blue: %d\n", min_color->blue);
        
    }
    if(strcmp(color, "red") == 0 && n > min_color->red) {
        min_color->red = n;
        printf("Changing Red, min_color->red: %d\n", min_color->red);
    }
    if(strcmp(color, "green") == 0 && n > min_color->green) {
        min_color->green = n; 
        printf("Changing Green, min_color->green: %d\n", min_color->green);
    }
}

void parse_set(char *set, struct Color *min_color) {
    char *sep = ","; 
    char *token; 
    char *save_pointer = NULL;
    token = strtok_r(set, sep, &save_pointer);
    int power = 1; 
    while(token != NULL) {
        // 12 red cubes, 13 green cubes, and 14 blue cubes
        set_power(token, min_color);
        token = strtok_r(NULL, sep, &save_pointer);
    }
}

int parse_line(char *line) {
    struct Color min_color = {0, 0, 0}; 
    char *save_pointer = NULL; 
    char *sep = ";";
    char *token; 
    int valid; 
    token = strtok_r(line, sep, &save_pointer);
    while(token != NULL) {
        parse_set(token, &min_color);
        token = strtok_r(NULL, sep, &save_pointer);
    }
    printf("(red: %d, blue: %d, green: %d\n)", min_color.red, min_color.blue, min_color.green);
    int power = min_color.red * min_color.blue * min_color.green;
    return power;
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
            int power = parse_line(sublime);
            printf("power: %d\n", power);
            sum = sum + power;            
            printf("  sum: %d\n", sum);
        }
    }
}