#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "puzzle2D.h"

int main(int argc, char *argv[]){

    char *ext = NULL;
    char *optional_ext = NULL; 
    char *word_list_name = NULL;
    char *puzzle_file_name = NULL;
    char *solution_file_name = NULL;
    int arg_count = 0;
    int word_length = 0;

    FILE* word_list;
    FILE* puzzle_file;
    FILE* solution; 

    if (argc != 7 && argc != 9) {
        fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
        exit(6);
    }
    
    // checking validity of command line arguments
    for (int i = 1; i < argc; i++) {
        ext = strrchr(argv[i], '.'); //gets the extension of a file if it has one
        
        if (ext != NULL){
            if (strcmp(ext+1, "txt") == 0){
                arg_count++;
                
                if (strcmp(argv[i-1], "-w") == 0){
                    word_list_name = argv[i];
                    arg_count++;
                }

                else if (strcmp(argv[i-1], "-p") == 0){
                    puzzle_file_name = argv[i];
                    arg_count++;
                } 
            }
        }

        else if (strcmp(argv[i], "-l") == 0){
            arg_count++;
            if ((atoi(argv[i+1]) > 0) || (atoi(argv[i+1]) < MAX_WORD_LEN)){
                word_length = atoi(argv[i+1]);
                arg_count++;
            }
        }
        
        else if (strcmp(argv[i], "-o") == 0){ 
            arg_count++;
            optional_ext = strrchr(argv[i+1], '.');
            if (optional_ext != NULL && strcmp(optional_ext+1, "txt") == 0 && arg_count < 8){
                solution_file_name = argv[i+1];
                arg_count++; 
            }
        }

        if (arg_count == 8){
            break;
        }
    }

    if (arg_count != 6 && arg_count != 8) { 
        fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
        exit(6);
    }
    
    else{
        if ((puzzle_file = fopen(puzzle_file_name, "r")) == NULL) {
            fprintf(stderr,"Error: Puzzle file %s does not exist\n", puzzle_file_name);
            exit(4);
        }
        else if ((word_list = fopen(word_list_name, "r")) == NULL) {
            fprintf(stderr,"Error: Input word file %s does not exist\n", word_list_name);
            exit(5);
        }
        if (solution_file_name != NULL) { 
            if ((solution = fopen(solution_file_name, "w")) == NULL) {
                fprintf(stderr,"Encountered error\n");
                exit(6);
            }
        }
    }
    
    
    int column = 0;
    int row = 0;

    char line[MAX_WORD_LEN];
    if (fgets(line, MAX_WORD_LEN, puzzle_file) != NULL) {
        column = strlen(line) - 1;
    }
    
    rewind(puzzle_file);

    char pords[MAX_WORD_LEN];
    while (fgets(pords, MAX_WORD_LEN, puzzle_file) != NULL) {
        if ( (int) (strlen(pords)-1) > column) {
            fprintf(stderr, "Encounted Error");
            exit(7);
        }
    }
    rewind(puzzle_file);

    char pines[MAX_GRID_SIZE];
    while (fgets(pines, MAX_GRID_SIZE, puzzle_file) != NULL && pines[0] != '\n') {
        row++;
    }

    char words[MAX_WORD_LEN];
    while (fgets(words, MAX_WORD_LEN, word_list) != NULL) {
        if ( (int) (strlen(words)-1) > word_length ) {
            fprintf(stderr, "Encounted Error");
            exit(7);
        }
    }

    if (row != column){
        fprintf(stderr, "Encounted Error");
        exit(7);
    }

    
    rewind(puzzle_file);
    rewind(word_list);

    char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            char c;
            fscanf(puzzle_file, "%c", &c);
            if (c >= 32 && c <= 126) {
                grid[i][j] = c;
            } 
            
            else {
                fprintf(stderr, "Encounted Error");
                exit(7);
            }
        }
        fscanf(puzzle_file, "\n");
    }
    
    rewind(puzzle_file);
    rewind(word_list);


    char word[MAX_GRID_SIZE];
    FILE *output = NULL;

    if (solution == NULL) {
        output = fopen("output.txt", "w");
    } 
    
    else {
        output = solution;
    }

    while (fgets(word, 100, word_list) != NULL && word[0] != '\n'){
        word[word_length] = '\0';
        search_word(output, grid, row, column, word, word_length);
    }

    if (output != NULL && output != solution) {
        fclose(output);
    }


    return 0;
}
    
    


