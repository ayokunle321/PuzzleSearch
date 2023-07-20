# Word Puzzle Search


## Purpose

The Word Puzzle Solver is a program designed to find a particular word in an n by n puzzle. It takes an input word list and an n by n puzzle grid, and then searches for the specified word within the puzzle. Once the word is found, the program provides the solution, indicating the exact location of the word in the puzzle grid.


## Execution

- Prepare your word list file (wordlist.txt) containing the words to search for in the puzzle.

- Create an n by n puzzle grid in a text file (puzzle.txt), ensuring that the puzzle dimensions match the size of the grid.

- Navigate to the current directory containing the program files.

- Use the following command in the terminal:

`make` to turn wordsearch2D.c to an executable file

`./wordSearch2D -l n -w wordlist.txt -p puzzle.txt`

Replace n with the appropriate word length and grid size.


# Files Included

- sample_test.sh: An executable bash script that contains the correct command (with the appropriate program arguments) to run the program wordSearch2D using the provided puzzle and word list text files.

- makefile - compiles and links the source files

In the src folder:

- wordsearch2D.c: Contains the main function and program argument checking logic.

- puzzle2d.c: Contains functions related to solving the word puzzle and searching for words in the grid.

- puzzle2D.h: Corresponding header file containing function prototypes for the puzzle2d.c module.


## Usage and Customization

The Word Puzzle Solver program can be adapted for various word search puzzles by changing the puzzle grid's size and the word list containing the words to search for. Feel free to modify the wordSearch2D program to fit your specific puzzle requirements.


## Contributions and Bug Reporting

If you encounter any issues or have suggestions to improve the program's performance, please consider contributing by creating a pull request or raising an issue in the repository. Contributions from the community are highly valued.