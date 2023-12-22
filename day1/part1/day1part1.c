// Written by Alicia M. Chun for the 2023 Advent of Code Day 1 Part 1 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int decode_line(char *line) {
    int len = strlen(line);
    int first = 0; 
    int last = 0;
    for (int i = 0; i < len; i++) {
        int ch = line[i];
        if(ch >= 48 && ch <= 57) {
            first = ch - 48; 
            break;
        }
    }

    for (int j = len - 1; j > -1; j--) {
        int ch = line[j];
        if (ch >= 48 && ch <= 57) {
            last = ch - 48;
            break;
        }
    }
    printf("     first: %d\n", first);
    printf("     last: %d\n", last); 
    return first * 10 + last; 
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
        while(fgets(line, 1000, fp) != NULL) {
            printf("line: %s \n", line);
            int value = decode_line(line);
            printf("  value: %d \n", value);
            sum += value;
            printf("  sum: %d \n", sum);
        }
        fclose(fp);
    }
    printf("Final sum: %d \n", sum);
}