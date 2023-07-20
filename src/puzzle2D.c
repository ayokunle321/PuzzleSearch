#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 101
#define MAX_GRID_SIZE 101
#define PRIME 7079
#define BASE 256

typedef struct {
    char word[MAX_WORD_LEN];
    int row;
    int col;
    int direction;
} WordLocation;

int get_hash(char* str, int len) {
    int h = 1;
    int i, curr_char, curr_hash = 0;
    for (i = 0; i < len; i++) {
        curr_char = str[i];
        curr_hash = (BASE * curr_hash + curr_char) % PRIME;
        h = (h * BASE) % PRIME;
    }
    return curr_hash;
}

int search_word(FILE *solution_file, char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col, char *word, int len){
    int found = 0;
    int word_hash = get_hash(word, len);
    int direction = 1;
    WordLocation location;
    strcpy(location.word, word);
    location.row = 0;
    location.col = 0;
    location.direction = 0;

    while (direction < 9) {
        switch (direction){ 
            case 1: // horizontal right
                for (int i = 0; i < row; i++) {
                    char str[len+1];
                    for (int j = 0; j < col; j++) {
                        if (j+len > col) {
                            break; 
                        }
                        
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i][j+k];
                        }
                        
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }

                        if (found) {
                            break;
                        }
                    }
                    
                    if (found) {
                        break;
                    }
                }
            break;
            
            case 2: //horizontal left
                for (int i = 0; i < row; i++) {
                    char str[len+1];
                    for (int j = len-1; j < col; j++) { 
                        if (j-len+1 < 0) {
                            break; 
                        }

                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i][j-k];
                        }
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }

                    if (found) {
                        break;
                    }
                }
            break;

            case 3: // vertical down
                for (int j = 0; j < col; j++) {
                    char str[len+1];
                    for (int i = 0; i <= row-len; i++) {
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i+k][j];
                        }
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }
                    
                    if (found) {
                        break;
                    }
                }
            break;

            case 4: // vertical up
                for (int j = col-1; j >= 0; j--) { 
                    char str[len+1];
                    for (int i = row-1; i >= 0; i--) {
                        if (i-len < -1) {
                            break;
                        }
                        
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i-k][j];
                        }
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }
                    
                    if (found) {
                        break;
                    }
                }
            break;

            case 5: // top left to bottom right diagonal
                for (int i = 0; i <= row - len; i++) {
                    for (int j = 0; j <= col - len; j++) {
                        char str[len+1];
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i+k][j+k];
                        }
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
            break;

            case 6: // bottom right to top left diagonal
                for (int i = row-1; i >= len-1; i--) {
                    char str[len+1];
                    for (int j = col-1; j >= len-1; j--) {
                        if (j-len < -1) {
                            break; 
                        }
                        
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i-k][j-k];
                        }
                        
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }

                    if (found) {
                        break;
                    }
                }
            break;

            case 7: // bottom left to top right diagonal
                for (int i = row-1; i >= len-1; i--) {
                    char str[len+1];
                    for (int j = 0; j <= col - len; j++) {
                        if (j+len > col) {
                            break;
                        }
                        
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i-k][j+k];
                        }
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }
                    
                    if (found) {
                        break;
                    }
                }
            break;

            case 8: // top right to bottom left diagonal (backwards)
                for (int i = 0; i <= row - len; i++) {
                    for (int j = col-1; j >= len-1; j--) {
                        char str[len+1];
                        for (int k = 0; k < len; k++) {
                            str[k] = grid[i+k][j-k];
                        }
                        str[len] = '\0';
                        int sub_hash = get_hash(str, len);
                        if (sub_hash == word_hash && strncmp(str, word, len) == 0) {
                            strcpy(location.word, word);
                            location.row = i;
                            location.col = j;
                            location.direction = direction;
                            found = 1;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
            break;
        } 

        if (found) {
            break;
        }
            
        else{
            direction++;
        }
    
    }
    fprintf(solution_file, "%s;(%d,%d);%d\n", location.word, location.row, location.col, location.direction);
    return found;
}

