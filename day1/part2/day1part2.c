// Written by Alicia M. Chun for the 2023 Advent of Code Day 1 Part 2
// Completed Dec. 21, 2023
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_in_line_from_beginning(char *line, char*substring) { // returns first index if the substring is in string, else returns -1

    for(int i = 0; i < strlen(line); i++) {
        for (int j = 0; j < strlen(substring); j++) {
            char subchar = substring[j]; 
            char linechar = line[i+j];
            if(linechar != subchar) {
                break;
            } 
            if(j == strlen(substring) - 1) {
                return i + j - strlen(substring) + 1;
            }
        }
    }
    return -1; 
}

int str_in_line_from_end(char *line, char*substring) { // returns first index if the substring is in string, else returns -1

    for(int i = strlen(line); i >= 0; i--) {
        for (int j = 0; j < strlen(substring); j++) {
            char subchar = substring[j]; 
            char linechar = line[i+j];
            if(linechar != subchar) {
                break;
            } 
            if(j == strlen(substring) - 1) {
                return i + j - strlen(substring) + 1;
            }
        }
    }
    return -1; 
}

int decode_line(char *line) {
    char *numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int min = strlen(line); // the minimum index before reaching a (word) number
    int min_num = 0; // value of the first number 
    int max = 0; // the maximum index before reaching a (word) number
    int max_num = 0; // value of the last number 

    // extracts the index and value of the first and last (word) number
    int idx; // the index of the current substring 
    for(int i = 0; i < 9; i++) {
        idx = str_in_line_from_beginning(line, numbers[i]);
        if(idx > -1 && idx < min) {
            min = idx;
            min_num = i + 1;
        }
    }

    for(int i = 0; i < 9; i++) {
        idx = str_in_line_from_end(line, numbers[i]);
        if (idx > -1 && idx >= max) {
            max = idx;
            max_num = i + 1;
        }
    }

    //extracts the index and value of the first and last (digit) number
    int c; 
    int m = min;
    for(int i = 0; i < m; i++) {
        c = line[i];
        if (c >= 49 && c <= 57) {
            min = i;
            min_num = c - 48; 
            break;
        }
    }
    m = max;
    for(int i = strlen(line) - 2; i >= m; i--) {
        c = line[i];
        if (c >= 49 && c <= 57) {
            max = i;
            max_num = c - 48; 
            break;
        }
    }
    return (min_num) * 10 + max_num;
}

int main(int argc, char *argv[]) {
    int sum = 0; 
    int value = 0; 
    if(argc > 1) {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("Unable to access file");
            exit(1);
        }
        char line[1000];
        while(fgets(line, 1000, fp) != NULL) {
            value = decode_line(line);
            sum += value; 
        }
        fclose(fp);
    }
    printf("sum: %d\n", sum);
}