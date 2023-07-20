#define MAX_WORD_LEN 101
#define MAX_GRID_SIZE 101

int get_hash(char* str, int len);
int search_word(FILE *solution_file, char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col, char *word, int len);
